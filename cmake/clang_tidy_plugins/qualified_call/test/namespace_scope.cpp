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
int target();
}
using other_ns::target;

void global_scope()
{
  target();
}

namespace unrelated
{
void outside_library()
{
  target();
}
}

namespace cub_extra
{
void similar_prefix()
{
  target();
}
}

namespace cuda_extra::std
{
void similar_prefix()
{
  target();
}
}

namespace user::cub
{
void nested_lookalike()
{
  target();
}
}

namespace user::cuda::std
{
void nested_lookalike()
{
  target();
}
}

namespace cub
{
void root()
{
  target();
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
namespace detail
{
void nested()
{
  target();
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
namespace
{
void anonymous_scope()
{
  target();
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

namespace cub
{
void reopened()
{
  target();
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

namespace cuda
{
namespace std
{
void traditional_syntax()
{
  target();
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

namespace cuda::std::ranges
{
void shorthand_syntax()
{
  target();
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

// CHECK-FIXES-NOT: DiagnosticName:

// clang-format on
