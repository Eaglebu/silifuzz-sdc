// Copyright 2022 The SiliFuzz Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "./snap/gen/snap_generator.h"

#include <sys/mman.h>

#include <cstdint>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "./common/mapped_memory_map.h"
#include "./common/memory_perms.h"
#include "./common/memory_state.h"
#include "./common/snapshot.h"
#include "./snap/exit_sequence.h"
#include "./snap/snap.h"
#include "./snap/testing/snap_generator_test_lib.h"
#include "./snap/testing/snap_test_snaps.h"
#include "./snap/testing/snap_test_snapshots.h"
#include "./snap/testing/snap_test_types.h"
#include "./util/testing/status_macros.h"
#include "./util/testing/status_matchers.h"

// Snap generator test.
// Test(s) below use pre-compiled Snaps in a SnapArray kSnapGeneratorTestSnaps,
// which are generated by an off-line generator from the Snapshots returned
// by MakeSnapGeneratorTestSnapshot(). We validate the generator by comparing
// the generated Snaps with the source Snapshots.

namespace silifuzz {

namespace {
using silifuzz::testing::StatusIs;

TEST(SnapGenerator, BasicSnapGeneratorTest) {
  Snapshot snapshot = MakeSnapGeneratorTestSnapshot(
      SnapGeneratorTestType::kBasicSnapGeneratorTest);
  const Snap& snap =
      GetSnapGeneratorTestSnap(SnapGeneratorTestType::kBasicSnapGeneratorTest);
  VerifyTestSnap(snapshot, snap,
                 SnapifyOptions::V2InputRunOpts(snapshot.architecture_id()));
}

TEST(SnapGenerator, MemoryBytesAttributesTest) {
  Snapshot snapshot = MakeSnapGeneratorTestSnapshot(
      SnapGeneratorTestType::kMemoryBytesPermsTest);
  const Snap& snap =
      GetSnapGeneratorTestSnap(SnapGeneratorTestType::kMemoryBytesPermsTest);
  VerifyTestSnap(snapshot, snap,
                 SnapifyOptions::V2InputRunOpts(snapshot.architecture_id()));

  // Check that any memory bytes in list that overlap with [start, limit)
  // must 1) completely lie inside [start, limit) and 2) is not writable.
  auto validate_memory_bytes_list =
      [](Snapshot::Address start, Snapshot::Address limit,
         const Snap::Array<Snap::MemoryBytes>& memory_bytes_list) {
        for (const auto& memory_bytes : memory_bytes_list) {
          const Snapshot::Address memory_bytes_limit =
              memory_bytes.start_address + memory_bytes.size();
          if (memory_bytes.start_address >= start &&
              memory_bytes_limit <= limit) {
            // memory bytes is completely inside [start,limit)
          } else {
            // Check that memory byte is completely outside of [start,limit).
            EXPECT_TRUE(memory_bytes_limit <= start ||
                        memory_bytes.start_address >= limit);
          }
        }
      };

  // Check that there is a code page and it is read-only.
  bool found_code = false;
  for (const auto& mapping : snap.memory_mappings) {
    if (mapping.perms & PROT_EXEC) {
      EXPECT_EQ(mapping.perms & PROT_WRITE, 0);
      validate_memory_bytes_list(mapping.start_address,
                                 mapping.start_address + mapping.num_bytes,
                                 mapping.memory_bytes);
      validate_memory_bytes_list(mapping.start_address,
                                 mapping.start_address + mapping.num_bytes,
                                 snap.end_state_memory_bytes);
      found_code = true;
    }
  }
  EXPECT_TRUE(found_code);
}

TEST(SnapGenerator, Snapify) {
  Snapshot snapshot = MakeSnapGeneratorTestSnapshot(
      SnapGeneratorTestType::kBasicSnapGeneratorTest);
  ASSERT_OK_AND_ASSIGN(const Snapshot snapified,
                       Snapify(snapshot, SnapifyOptions::V2InputRunOpts(
                                             snapshot.architecture_id())));

  for (const auto& mapping : snapified.memory_mappings()) {
    MemoryPerms expected_perms = snapshot.PermsAt(mapping.start_address());
    EXPECT_EQ(mapping.perms().DebugString(), expected_perms.DebugString());
  }

  // Check that we have the exit sequence in the initial memory bytes.
  MemoryState initial_memory_state =
      MemoryState::MakeInitial(snapified, MemoryState::kZeroMappedBytes);

  const Snapshot::EndState snapified_end_state =
      snapified.expected_end_states()[0];
  const Snapshot::Address snapified_end_state_rip =
      snapified_end_state.endpoint().instruction_address();
  const size_t exit_sequence_size = GetSnapExitSequenceSize<Host>();
  ASSERT_TRUE(initial_memory_state.mapped_memory().Contains(
      snapified_end_state_rip, snapified_end_state_rip + exit_sequence_size));
  const Snapshot::ByteData exit_sequence = initial_memory_state.memory_bytes(
      snapified_end_state_rip, exit_sequence_size);
  std::string expected_exit_sequence(exit_sequence_size, 0);
  WriteSnapExitSequence<Host>(expected_exit_sequence.data());
  EXPECT_EQ(exit_sequence, expected_exit_sequence);

  // All end state memory bytes must be writable as in the original snapshot.
  // There should not be read-only memory bytes.
  for (const auto& memory_bytes : snapified_end_state.memory_bytes()) {
    EXPECT_TRUE(snapshot.mapped_memory_map()
                    .PermsAt(memory_bytes.start_address())
                    .Has(MemoryPerms::kWritable));
    initial_memory_state.RemoveMemoryMapping(memory_bytes.start_address(),
                                             memory_bytes.limit_address());
  }
  initial_memory_state.mapped_memory().Iterate(
      [&initial_memory_state](auto start, auto limit, auto p) {
        EXPECT_FALSE(p.Has(MemoryPerms::kWritable))
            << "Expected that all writable pages are present in the end state. "
            << "Snapshot mappings missing from end state: "
            << initial_memory_state.mapped_memory().DebugString();
      });
}

TEST(SnapGenerator, SnapifyIdempotent) {
  Snapshot snapshot = MakeSnapGeneratorTestSnapshot(
      SnapGeneratorTestType::kBasicSnapGeneratorTest);

  SnapifyOptions opts =
      SnapifyOptions::V2InputRunOpts(snapshot.architecture_id());
  ASSERT_OK_AND_ASSIGN(const Snapshot snapified, Snapify(snapshot, opts));
  ASSERT_OK_AND_ASSIGN(const Snapshot snapified2, Snapify(snapified, opts));
  ASSERT_EQ(snapified, snapified2);
}

TEST(SnapGenerator, CanSnapify) {
  Snapshot snapshot = MakeSnapGeneratorTestSnapshot(
      SnapGeneratorTestType::kBasicSnapGeneratorTest);
  snapshot.set_expected_end_states({});
  SnapifyOptions opts =
      SnapifyOptions::V2InputRunOpts(snapshot.architecture_id());
  EXPECT_THAT(CanSnapify(snapshot, opts),
              StatusIs(absl::StatusCode::kNotFound));
  EXPECT_THAT(Snapify(snapshot, opts), StatusIs(absl::StatusCode::kNotFound));
}

}  // namespace
}  // namespace silifuzz
