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

#include "./snap/gen/relocatable_snap_generator.h"

#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/status/status.h"
#include "./common/memory_mapping.h"
#include "./common/memory_perms.h"
#include "./common/snapshot.h"
#include "./common/snapshot_test_enum.h"
#include "./common/snapshot_test_util.h"
#include "./snap/gen/snap_generator.h"
#include "./snap/snap.h"
#include "./snap/snap_checksum.h"
#include "./snap/snap_relocator.h"
#include "./snap/snap_util.h"
#include "./snap/testing/snap_generator_test_lib.h"
#include "./snap/testing/snap_test_snapshots.h"
#include "./util/arch.h"
#include "./util/checks.h"
#include "./util/mmapped_memory_ptr.h"
#include "./util/testing/status_macros.h"
#include "./util/ucontext/serialize.h"
#include "./util/ucontext/ucontext_types.h"

namespace silifuzz {
namespace {

// Helper to serialize register state.
template <typename Arch>
Snapshot::RegisterState BuildRegisterState(const GRegSet<Arch>& gregs,
                                           const FPRegSet<Arch>& fpregs) {
  Snapshot::ByteData gregs_byte_data, fpregs_byte_data;
  CHECK(SerializeGRegs(gregs, &gregs_byte_data));
  CHECK(SerializeFPRegs(fpregs, &fpregs_byte_data));
  return {gregs_byte_data, fpregs_byte_data};
}

// Generates a relocatable corpus from source `snapshots` and relocates it
// to the mmap buffer address.
template <typename Arch>
MmappedMemoryPtr<const SnapCorpus<Arch>> GenerateRelocatedCorpus(
    const std::vector<Snapshot>& snapshots,
    const RelocatableSnapGeneratorOptions& options = {}) {
  auto relocatable =
      GenerateRelocatableSnaps(Arch::architecture_id, snapshots, options);
  SnapRelocatorError error;
  auto relocated_corpus =
      SnapRelocator<Arch>::RelocateCorpus(std::move(relocatable), true, &error);
  CHECK(error == SnapRelocatorError::kOk);
  CHECK_EQ(relocated_corpus->snaps.size, snapshots.size());
  return relocated_corpus;
}

template <typename>
struct RelocatableSnapGenerator : ::testing::Test {};
using arch_typelist = ::testing::Types<ALL_ARCH_TYPES>;
TYPED_TEST_SUITE(RelocatableSnapGenerator, arch_typelist);

// Test that undefined end state does not crash the generator.
TYPED_TEST(RelocatableSnapGenerator, UndefinedEndState) {
  // Create an empty snapshot with no end state.
  Snapshot snapshot =
      CreateTestSnapshot<TypeParam>(TestSnapshot::kSigSegvWrite);
  ASSERT_TRUE(snapshot.IsComplete(Snapshot::kUndefinedEndState).ok())
      << "Expected that this snapshot has an undefined end state";

  SnapifyOptions snapify_options =
      SnapifyOptions::V2InputRunOpts(snapshot.architecture_id());
  snapify_options.allow_undefined_end_state = true;
  // Note: it isn't guaranteed that all the test snaps will be snap
  // compatible. If this becomes an issue, we can add a query function and
  // filter them out here.
  ASSERT_OK_AND_ASSIGN(Snapshot snapified, Snapify(snapshot, snapify_options));
  std::vector<Snapshot> corpus;
  corpus.push_back(std::move(snapified));
  auto relocated_corpus = GenerateRelocatedCorpus<TypeParam>(corpus);
  EXPECT_EQ(relocated_corpus->snaps.at(0)->id, snapshot.id());
}

TYPED_TEST(RelocatableSnapGenerator, RoundTrip) {
  std::vector<Snapshot> corpus;
  Snapshot snapshot =
      MakeSnapRunnerTestSnapshot<TypeParam>(TestSnapshot::kEndsAsExpected);

  {
    SnapifyOptions snapify_options =
        SnapifyOptions::V2InputRunOpts(snapshot.architecture_id());
    ASSERT_OK_AND_ASSIGN(Snapshot snapified,
                         Snapify(snapshot, snapify_options));
    corpus.push_back(std::move(snapified));
  }

  auto relocated_corpus = GenerateRelocatedCorpus<TypeParam>(corpus);
  auto snapshotFromSnap = SnapToSnapshot(*relocated_corpus->snaps.at(0),
                                         TestSnapshotPlatform<TypeParam>());
  ASSERT_OK(snapshotFromSnap);
  ASSERT_EQ(corpus[0], *snapshotFromSnap);
}

TYPED_TEST(RelocatableSnapGenerator, SupportDirectMMap) {
  std::vector<Snapshot> rle_corpus;
  {
    Snapshot snapshot =
        MakeSnapRunnerTestSnapshot<TypeParam>(TestSnapshot::kEndsAsExpected);

    SnapifyOptions snapify_options =
        SnapifyOptions::V2InputRunOpts(snapshot.architecture_id());
    snapify_options.compress_repeating_bytes = true;
    snapify_options.support_direct_mmap = false;

    ASSERT_OK_AND_ASSIGN(Snapshot snapified,
                         Snapify(snapshot, snapify_options));
    rle_corpus.push_back(std::move(snapified));
  }

  auto relocated_rle_corpus = GenerateRelocatedCorpus<TypeParam>(rle_corpus);

  std::vector<Snapshot> mmap_corpus;
  {
    Snapshot snapshot =
        MakeSnapRunnerTestSnapshot<TypeParam>(TestSnapshot::kEndsAsExpected);

    SnapifyOptions snapify_options =
        SnapifyOptions::V2InputRunOpts(snapshot.architecture_id());
    snapify_options.compress_repeating_bytes = true;
    snapify_options.support_direct_mmap = true;

    ASSERT_OK_AND_ASSIGN(Snapshot snapified,
                         Snapify(snapshot, snapify_options));
    mmap_corpus.push_back(std::move(snapified));
  }

  auto relocated_mmap_corpus = GenerateRelocatedCorpus<TypeParam>(mmap_corpus);

  // The mmap corpus should be bigger because it does not compress executable
  // pages.
  EXPECT_LT(MmappedMemorySize(relocated_rle_corpus) + 3072,
            MmappedMemorySize(relocated_mmap_corpus));

  // But it shouldn't me more that 2 pages larger - one for fragmentation, one
  // for the uncompressed page.
  EXPECT_GT(MmappedMemorySize(relocated_rle_corpus) + 8192,
            MmappedMemorySize(relocated_mmap_corpus));

  // Check invariants.
  ASSERT_EQ(relocated_rle_corpus->snaps.size, 1);
  ASSERT_EQ(relocated_mmap_corpus->snaps.size, 1);

  // Check invariants for rle executable page.
  bool found = false;
  for (auto& memory_mapping :
       relocated_rle_corpus->snaps.at(0)->memory_mappings) {
    if (memory_mapping.perms & PROT_EXEC) {
      found = true;
      ASSERT_GT(memory_mapping.memory_bytes.size, 1);
    }
  }
  EXPECT_TRUE(found);

  // Check invariants for mmap executable page.
  found = false;
  for (auto& memory_mapping :
       relocated_mmap_corpus->snaps.at(0)->memory_mappings) {
    if (memory_mapping.perms & PROT_EXEC) {
      found = true;
      ASSERT_EQ(memory_mapping.memory_bytes.size, 1);
      const SnapMemoryBytes& memory_bytes = memory_mapping.memory_bytes[0];
      ASSERT_FALSE(memory_bytes.repeating());
      EXPECT_EQ(
          reinterpret_cast<uintptr_t>(memory_bytes.data.byte_values.elements) %
              4096,
          0);
      EXPECT_EQ(memory_bytes.data.byte_values.size % 4096, 0);
    }
  }
  EXPECT_TRUE(found);
}

TYPED_TEST(RelocatableSnapGenerator, AllRunnerTestSnaps) {
  SnapifyOptions opts = SnapifyOptions::V2InputRunOpts(Host::architecture_id);

  // Generate relocatable snaps from runner test snaps.
  std::vector<Snapshot> snapified_corpus;
  for (int index = 0; index < static_cast<int>(TestSnapshot::kNumTestSnapshot);
       ++index) {
    TestSnapshot type = static_cast<TestSnapshot>(index);
    if (!TestSnapshotExists<TypeParam>(type)) {
      continue;
    }
    Snapshot snapshot = MakeSnapRunnerTestSnapshot<TypeParam>(type);
    ASSERT_OK_AND_ASSIGN(Snapshot snapified, Snapify(snapshot, opts));
    snapified_corpus.push_back(std::move(snapified));
  }

  auto relocated_corpus = GenerateRelocatedCorpus<TypeParam>(snapified_corpus);

  // Verify relocated Snap corpus is equivalent to the original Snapshots.
  ASSERT_EQ(snapified_corpus.size(), relocated_corpus->snaps.size);
  for (size_t i = 0; i < snapified_corpus.size(); ++i) {
    const Snapshot& snapshot = snapified_corpus[i];
    const Snap<TypeParam>& snap = *relocated_corpus->snaps.at(i);
    VerifyTestSnap(snapshot, snap, opts);
  }
}

// Test that duplicated byte data are merged to a single copy.
TYPED_TEST(RelocatableSnapGenerator, DedupeMemoryBytes) {
  Snapshot snapshot =
      CreateTestSnapshot<TypeParam>(TestSnapshot::kEndsAsExpected);

  const size_t page_size = getpagesize();
  Snapshot::ByteData test_byte_data("This is a test");
  // Fill page with non repeating data. Otherwise run-length compression splits
  // this into 2 MemoryBytes objects and that will confuse the check for
  // de-duplication below.
  test_byte_data.reserve(page_size);
  for (size_t i = test_byte_data.size(); i < page_size; ++i) {
    test_byte_data.push_back(i % 256);
  }

  // Helper to add test_byte_data at `address`
  auto add_test_byte_data = [&](Snapshot::Address address) {
    const MemoryMapping mapping =
        MemoryMapping::MakeSized(address, page_size, MemoryPerms::R());
    ASSERT_OK(snapshot.can_add_memory_mapping(mapping));
    snapshot.add_memory_mapping(mapping);
    const Snapshot::MemoryBytes memory_bytes(address, test_byte_data);
    ASSERT_OK(snapshot.can_add_memory_bytes(memory_bytes));
    snapshot.add_memory_bytes(memory_bytes);
  };

  // Construct two memory bytes with identical byte data.
  const Snapshot::Address addr1 = 0x6502 * page_size;
  const Snapshot::Address addr2 = 0x8086 * page_size;
  add_test_byte_data(addr1);
  add_test_byte_data(addr2);

  SnapifyOptions snapify_opts =
      SnapifyOptions::V2InputRunOpts(snapshot.architecture_id());
  ASSERT_OK_AND_ASSIGN(auto snapified, Snapify(snapshot, snapify_opts));

  std::vector<Snapshot> snapified_corpus;
  snapified_corpus.push_back(std::move(snapified));

  absl::flat_hash_map<std::string, uint64_t> counters;
  auto relocated_corpus = GenerateRelocatedCorpus<TypeParam>(
      snapified_corpus, {.counters = &counters});
  // Hard to find a reasonable expected value that doesn't vary between x86
  // and ARM. "string_block" is the size of snapshot id (kEndsAsExpected) in
  // asciiz.
  EXPECT_EQ(counters["string_block"], 16);

  // Test byte data should appear twice in two MemoryBytes objects but
  // the array element addresses should be the same.
  ASSERT_EQ(relocated_corpus->snaps.size, 1);
  const Snap<TypeParam>& snap = *relocated_corpus->snaps.at(0);
  absl::flat_hash_set<const uint8_t*> addresses_seen;
  int times_seen = 0;
  for (const auto& mapping : snap.memory_mappings) {
    for (const auto& memory_bytes : mapping.memory_bytes) {
      if (!memory_bytes.repeating() &&
          memory_bytes.size() == test_byte_data.size() &&
          memcmp(memory_bytes.data.byte_values.elements, test_byte_data.data(),
                 test_byte_data.size()) == 0) {
        times_seen++;
        addresses_seen.insert(memory_bytes.data.byte_values.elements);
      }
    }
  }
  EXPECT_EQ(times_seen, 2);
  EXPECT_EQ(addresses_seen.size(), 1);
}

// Test register memory checksums.
TYPED_TEST(RelocatableSnapGenerator, RegisterMemoryChecksums) {
  Snapshot snapshot =
      CreateTestSnapshot<TypeParam>(TestSnapshot::kEndsAsExpected);
  Snapshot::Address pc = snapshot.ExtractRip(snapshot.registers());
  Snapshot::Address sp = snapshot.ExtractRsp(snapshot.registers());
  ASSERT_EQ(snapshot.expected_end_states().size(), 1);
  const Snapshot::EndState& end_state = snapshot.expected_end_states()[0];
  Snapshot::Address end_state_pc = snapshot.ExtractRip(end_state.registers());
  Snapshot::Address end_state_sp = snapshot.ExtractRsp(end_state.registers());

  // Set ending register state to be some non-zero values.
  // Use sane PC and stack pointer values so that Snapify() is happy.
  GRegSet<TypeParam> gregs, end_state_gregs;
  FPRegSet<TypeParam> fpregs, end_state_fpregs;
  memset(&gregs, 0xaa, sizeof(gregs));
  gregs.SetInstructionPointer(pc);
  gregs.SetStackPointer(sp);
  memset(&fpregs, 0xbb, sizeof(fpregs));
  memset(&end_state_gregs, 0xcc, sizeof(end_state_gregs));
  end_state_gregs.SetInstructionPointer(end_state_pc);
  end_state_gregs.SetStackPointer(end_state_sp);
  memset(&end_state_fpregs, 0xdd, sizeof(end_state_fpregs));
  Snapshot::EndState new_end_state(
      end_state.endpoint(),
      BuildRegisterState(end_state_gregs, end_state_fpregs));
  new_end_state.set_platforms(end_state.platforms());
  snapshot.set_expected_end_states({new_end_state});
  SnapifyOptions snapify_opts =
      SnapifyOptions::V2InputMakeOpts(snapshot.architecture_id());
  ASSERT_OK_AND_ASSIGN(auto snapified, Snapify(snapshot, snapify_opts));

  std::vector<Snapshot> snapified_corpus;
  snapified_corpus.push_back(std::move(snapified));
  auto relocated_corpus = GenerateRelocatedCorpus<TypeParam>(snapified_corpus);

  ASSERT_EQ(relocated_corpus->snaps.size, 1);
  const Snap<TypeParam>& snap = *relocated_corpus->snaps[0];
  SnapRegisterMemoryChecksum<TypeParam> register_memory_checksum =
      CalculateRegisterMemoryChecksum(snap.registers);
  EXPECT_EQ(register_memory_checksum, snap.registers_memory_checksum);
  SnapRegisterMemoryChecksum<TypeParam> end_state_register_memory_checksum =
      CalculateRegisterMemoryChecksum(snap.end_state_registers);
  EXPECT_EQ(end_state_register_memory_checksum,
            snap.end_state_registers_memory_checksum);
}

// Test register deduplication.
TYPED_TEST(RelocatableSnapGenerator, DedupeRegisterBytes) {
  Snapshot snapshot =
      CreateTestSnapshot<TypeParam>(TestSnapshot::kEndsAsExpected);
  // Make ending register state ot be identical to initial state to
  // test deplication.
  Snapshot::EndState old_end_state = snapshot.expected_end_states()[0];
  Snapshot::EndState end_state(old_end_state.endpoint(), snapshot.registers());
  end_state.set_platforms(old_end_state.platforms());
  snapshot.set_expected_end_states({end_state});

  SnapifyOptions snapify_opts =
      SnapifyOptions::V2InputMakeOpts(snapshot.architecture_id());
  ASSERT_OK_AND_ASSIGN(auto snapified, Snapify(snapshot, snapify_opts));

  std::vector<Snapshot> snapified_corpus;
  snapified_corpus.push_back(std::move(snapified));
  auto relocated_corpus = GenerateRelocatedCorpus<TypeParam>(snapified_corpus);

  ASSERT_EQ(relocated_corpus->snaps.size, 1);
  const Snap<TypeParam>& snap = *relocated_corpus->snaps[0];
  EXPECT_EQ(snap.registers.gregs, snap.end_state_registers.gregs);
  EXPECT_EQ(snap.registers.fpregs, snap.end_state_registers.fpregs);
}

}  // namespace
}  // namespace silifuzz
