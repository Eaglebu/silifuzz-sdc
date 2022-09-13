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

#ifndef THIRD_PARTY_SILIFUZZ_UTIL_UCONTEXT_UCONTEXT_TYPES_H_
#define THIRD_PARTY_SILIFUZZ_UTIL_UCONTEXT_UCONTEXT_TYPES_H_

#include <string.h>    // for memcmp()
#include <ucontext.h>  // for gregset_t and fpregset_t

#include <cstdint>
#include <type_traits>  // for std::remove_pointer

namespace silifuzz {

// Values for all general-purpose CPU registers.
// This has the same layout as gregset_t from ucontext_t up to the ss field
// (our test verifies that), but overall this has the exact structure
// of (and only) the register state that can be saved - see SaveUContext().
#if defined(__x86_64__)
struct GRegSet {
  uint64_t r8;
  uint64_t r9;
  uint64_t r10;
  uint64_t r11;
  uint64_t r12;
  uint64_t r13;
  uint64_t r14;
  uint64_t r15;
  uint64_t rdi;
  uint64_t rsi;
  uint64_t rbp;
  uint64_t rbx;
  uint64_t rdx;
  uint64_t rax;
  uint64_t rcx;
  uint64_t rsp;
  uint64_t rip;
  uint64_t eflags;
  uint16_t cs;
  uint16_t gs;
  uint16_t fs;
  uint16_t ss;  // padding in gregset_t; fields after this differ from gregset_t
  uint16_t ds;
  uint16_t es;
  uint32_t padding;  // so that sizeof(GRegSet) is a multiple of int64, so that
                     // there is no unnamed padding in UContext below
                     // (our test verifies this)
  // FS_BASE and GS_BASE are hidden base registers used to compute fs: and gs:
  // relative addresses in 64-bit mode.
  // See "4.5.3 Segment Registers in 64-Bit Mode" in  AMD64 Architecture
  // Programmer’s Manual Volume 2: System Programming
  // https://www.amd.com/system/files/TechDocs/24593.pdf
  // On Linux fs_base is typically used to refer to TLS data.
  uint64_t fs_base;
  uint64_t gs_base;
};
#elif defined(__aarch64__)
struct GRegSet {
  uint64_t x[31];
  uint64_t sp;
  uint64_t pc;
  uint64_t pstate;
  uint64_t tpidr;
  uint64_t tpidrro;
};
#else
#error "Unsupported architecture"
#endif

// Convenience equality on GRegSet (all bytes are compared).
inline bool operator==(const GRegSet& x, const GRegSet& y) {
  return 0 == memcmp(&x, &y, sizeof(GRegSet));
}
inline bool operator!=(const GRegSet& x, const GRegSet& y) { return !(x == y); }

// ========================================================================= //

#if defined(__x86_64__)
// Values for all floating point CPU registers.
// The struct to which a fpregset_t points to is not public in ucontext.h,
// but we can get to it with <type_traits>.
// Note: Linux's fpregset_t is not aligned correctly to be used with fxsave, so
// we're forcing it using __aligned__. alignas cannot be used in all the places
// that __aligned__ can be, so we're using a slightly non-standard approach.
static_assert(alignof(std::remove_pointer<fpregset_t>::type) <= 16,
              "Underlying data type has larger alignment than expected.");
static_assert(sizeof(std::remove_pointer<fpregset_t>::type) % 16 == 0,
              "Underlying data type size is unexpected.");
using FPRegSet __attribute__((__aligned__(16))) =
    std::remove_pointer<fpregset_t>::type;
static_assert(alignof(FPRegSet) == 16, "FPRegSet has unexpected alignment.");
#elif defined(__aarch64__)
// Note: libc stores fpsr and fpcr as 32-bit values. This structure stores them
// as 64-bit values because that is they way they are specified. Currently the
// upper 32-bits are zero, but that could technically change.
struct FPRegSet {
  __uint128_t v[32];
  uint64_t fpsr;
  uint64_t fpcr;
};
static_assert(alignof(FPRegSet) == 16, "FPRegSet has unexpected alignment.");
#else
#error "Unsupported architecture"
#endif

// Convenience equality on FPRegSet (all bytes are compared).
inline bool operator==(const FPRegSet& x, const FPRegSet& y) {
  return 0 == memcmp(&x, &y, sizeof(FPRegSet));
}
inline bool operator!=(const FPRegSet& x, const FPRegSet& y) {
  return !(x == y);
}

// ========================================================================= //

// UContext contains complete user-space CPU execution context state.
//
// Very similar to ucontext_t from libc, but unlike it:
// * We have a convenient way of accessing general registers (struct fields vs.
//   indexing into an array - see GRegSet above).
// * We have space for all segment registers.
// * We do not store data unrelated to CPU state.
// * We guarantee alignment of 16 for FPRegSet field, so that
//   our context saving/restoring implementations can easily use the fxsave and
//   fxrstor instructions that require this alignment.
struct UContext {
  FPRegSet fpregs;
  GRegSet gregs;

  UContext();

  // Helper struct for constexpr initialization.
  struct ConstexprInit {
    FPRegSet fpregs;
    GRegSet gregs;
  };

  // This is used in generated code for Snap. A ConstexprInit is implicitly
  // converted to a constexpr UContext. We cannot use the no argument
  // constructor below for constexpr.
  //
  // Usage:
  // constexpr UContext u = ConstexprInit({ .fpregs = {...}, .gregs = {...} };
  //
  constexpr UContext(const ConstexprInit& init)
      : fpregs(init.fpregs), gregs(init.gregs) {
    // Alignment of UContext initialized by
    // this constructor is handled by the linker. Hence we do not need to
    // perform a runtime alignment check as in the no argument constructor.
  }
};

static_assert(sizeof(UContext) == sizeof(FPRegSet) + sizeof(GRegSet),
              "UContext should not have internal padding.");
static_assert(alignof(UContext) >= alignof(FPRegSet),
              "Aligning fpregs should have aligned UContext.");

}  // namespace silifuzz

#endif  // THIRD_PARTY_SILIFUZZ_UTIL_UCONTEXT_UCONTEXT_TYPES_H_