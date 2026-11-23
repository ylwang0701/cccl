// SPDX-FileCopyrightText: Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// clang-format off
// CLANG_TIDY_CONFIG_BEGIN
// Checks: cccl-qualified-call
// CLANG_TIDY_CONFIG_END

// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

namespace other_ns
{
constexpr int target()
{
  return 1;
}
}
using other_ns::target;

namespace cub
{
int namespace_initializer = target();
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

inline int inline_initializer = target();
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

void default_argument(int value = target());
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

struct object
{
  int member = target();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: FileOffset: [[#CALL:]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES: Notes:
  // CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
  // CHECK-FIXES: FileOffset: [[#CALL]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

  object() : member(target())
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: FileOffset: [[#CALL:]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES: Notes:
  // CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
  // CHECK-FIXES: FileOffset: [[#CALL]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
  {}

  int method()
  {
    return target();
    // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
    // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
    // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
    // CHECK-FIXES: FileOffset: [[#CALL:]]
    // CHECK-FIXES: Replacements: []
    // CHECK-FIXES: Notes:
    // CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
    // CHECK-FIXES: FileOffset: [[#CALL]]
    // CHECK-FIXES: Replacements: []
    // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
    // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
    // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
  }
};

void lambda_contexts()
{
  auto lambda = [value = target()] {
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: FileOffset: [[#CALL:]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES: Notes:
  // CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
  // CHECK-FIXES: FileOffset: [[#CALL]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
    return target() + value;
    // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
    // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
    // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
    // CHECK-FIXES: FileOffset: [[#CALL:]]
    // CHECK-FIXES: Replacements: []
    // CHECK-FIXES: Notes:
    // CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
    // CHECK-FIXES: FileOffset: [[#CALL]]
    // CHECK-FIXES: Replacements: []
    // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
    // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
    // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
  };
  (void) lambda();
  (void) [] {
    return target();
    // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
    // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
    // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
    // CHECK-FIXES: FileOffset: [[#CALL:]]
    // CHECK-FIXES: Replacements: []
    // CHECK-FIXES: Notes:
    // CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
    // CHECK-FIXES: FileOffset: [[#CALL]]
    // CHECK-FIXES: Replacements: []
    // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
    // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
    // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
  }();
}

void local_class_context()
{
  struct local
  {
    int method()
    {
      return target();
      // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
      // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
      // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
      // CHECK-FIXES: FileOffset: [[#CALL:]]
      // CHECK-FIXES: Replacements: []
      // CHECK-FIXES: Notes:
      // CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
      // CHECK-FIXES: FileOffset: [[#CALL]]
      // CHECK-FIXES: Replacements: []
      // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
      // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
      // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
    }
  };
}

using expression_type = decltype(target());
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

using function_type = void() noexcept(noexcept(target()));
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

inline constexpr int array_size = sizeof(target());
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

enum
{
  enumerator = target()
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: FileOffset: [[#CALL:]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES: Notes:
  // CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
  // CHECK-FIXES: FileOffset: [[#CALL]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
};

int array[target()];
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

template <int Value = target()>
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
struct default_template_argument {};

template <class T>
int variable_template = target();
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

auto trailing_return() -> decltype(target());
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

int exception_specification() noexcept(noexcept(target()));
// CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
// CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
// CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
// CHECK-FIXES: FileOffset: [[#CALL:]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES: Notes:
// CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
// CHECK-FIXES: FileOffset: [[#CALL]]
// CHECK-FIXES: Replacements: []
// CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

void default_argument_use()
{
  ::cub::default_argument();
}

extern "C"
{
int linkage_context()
{
  return target();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'other_ns'
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: FileOffset: [[#CALL:]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES: Notes:
  // CHECK-FIXES: Message: 'Call appears to originate from namespace ''other_ns'''
  // CHECK-FIXES: FileOffset: [[#CALL]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
}
}
}

// CHECK-FIXES-NOT: DiagnosticName:

// clang-format on
