// Copyright 2023 The SiliFuzz Authors.
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

#include "./util/arch.h"

#include "gtest/gtest.h"

namespace silifuzz {

namespace {

template <class Arch>
int ReturnArchValue() {
  return static_cast<int>(Arch::architecture_id);
}

template <class Arch>
int MACArchValue(int a, int b) {
  return static_cast<int>(Arch::architecture_id) * a + b;
}

template <class Arch>
void MutateArg(int& arch) {
  arch = static_cast<int>(Arch::architecture_id);
}

using arch_typelist = testing::Types<ALL_ARCH_TYPES>;

template <class>
struct ArchTest : testing::Test {};
TYPED_TEST_SUITE(ArchTest, arch_typelist);

TYPED_TEST(ArchTest, ArchDispatchZeroArgs) {
  EXPECT_EQ(ARCH_DISPATCH(ReturnArchValue, TypeParam::architecture_id),
            static_cast<int>(TypeParam::architecture_id));
}

TYPED_TEST(ArchTest, ArchDispatchSomeArgs) {
  for (int b = -2; b <= 2; ++b) {
    for (int a = -2; a <= 2; ++a) {
      EXPECT_EQ(ARCH_DISPATCH(MACArchValue, TypeParam::architecture_id, a, b),
                static_cast<int>(TypeParam::architecture_id) * a + b);
    }
  }
}

TYPED_TEST(ArchTest, ArchDispatchOutputParam) {
  int tmp = -1;
  ARCH_DISPATCH(MutateArg, TypeParam::architecture_id, tmp);
  EXPECT_EQ(tmp, static_cast<int>(TypeParam::architecture_id));
}

}  // namespace

}  // namespace silifuzz