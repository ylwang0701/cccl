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
struct external
{
  static void call();
};
}

namespace cub
{
struct outer_type
{
  static void call();
};
inline namespace abi
{
struct inline_type
{
  static void call();
};
inline namespace version
{
template <class T>
struct inline_template
{
  static void call();
};
void nested_inline()
{
  outer_type::call();
  inline_type::call();
  inline_template<int>::call();
  other_ns::external::call();
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
inline namespace sibling
{
void sibling_inline()
{
  inline_type::call();
  inline_template<int>::call();
}
}
void enclosing_namespace()
{
  inline_type::call();
  abi::inline_type::call();
  inline_template<int>::call();
}
namespace detail
{
void ordinary_boundary()
{
  inline_type::call();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'cub'
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: FileOffset: [[#CALL:]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES: Notes:
  // CHECK-FIXES: Message: 'Call appears to originate from namespace ''cub'''
  // CHECK-FIXES: FileOffset: [[#CALL]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
  outer_type::call();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'cub'
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: FileOffset: [[#CALL:]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES: Notes:
  // CHECK-FIXES: Message: 'Call appears to originate from namespace ''cub'''
  // CHECK-FIXES: FileOffset: [[#CALL]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
}
inline namespace detail_abi
{
void boundary_below_inline()
{
  inline_type::call();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-MESSAGES: :[[@LINE-2]]:{{[0-9]+}}: note: Call appears to originate from namespace 'cub'
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: FileOffset: [[#CALL:]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES: Notes:
  // CHECK-FIXES: Message: 'Call appears to originate from namespace ''cub'''
  // CHECK-FIXES: FileOffset: [[#CALL]]
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
}
}
}
inline namespace abi
{
void reopened_inline()
{
  inline_type::call();
  outer_type::call();
}
}
}

// Inline ABI namespaces can appear above and below std.
namespace cuda
{
inline namespace abi
{
namespace std
{
struct outer_type
{
  static void call();
};
inline namespace version
{
struct inline_type
{
  static void call();
};
void operations()
{
  outer_type::call();
  inline_type::call();
  other_ns::external::call();
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
void operations()
{
  inline_type::call();
}
}
}
}

// CHECK-FIXES-NOT: DiagnosticName:

// clang-format on
