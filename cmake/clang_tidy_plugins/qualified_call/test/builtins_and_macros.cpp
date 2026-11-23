// SPDX-FileCopyrightText: Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// clang-format off
// CLANG_TIDY_CONFIG_BEGIN
// Checks: cccl-qualified-call
// CLANG_TIDY_CONFIG_END

// CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
// CHECK-MESSAGES-NOT: note: Call appears to originate from namespace

namespace cub
{
long value();
void __builtin_user_function();

void compiler_builtins(char* output, const char* input, int& integer)
{
  (void) __builtin_expect(integer != 0, 1);
  (void) __builtin_strlen(input);
  (void) __builtin_memcpy(output, input, 1);
  (void) __builtin_addressof(integer);
  (void) ::__builtin_expect(integer != 0, 1);
}

template <class T>
long dependent_builtin(T condition)
{
  return __builtin_expect(static_cast<bool>(condition), 1);
}

void ordinary_function_with_builtin_prefix()
{
  __builtin_user_function();
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
  ::cub::__builtin_user_function();
}

void builtin_argument()
{
  (void) __builtin_expect(value(), 1);
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
  (void) __builtin_expect(::cub::value(), 1);
}
}

int target();
namespace other_ns
{
int target();
}

#define CALL_BARE() target()
#define CALL_RELATIVE() other_ns::target()
#define CALL_GLOBAL() ::target()
#define EXPECT_TRUE(expression) __builtin_expect(static_cast<bool>(expression), 1)
#define FORWARD_EXPRESSION(expression) (expression)

namespace cub
{
void macro_calls()
{
  CALL_BARE();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
  CALL_RELATIVE();
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
  CALL_GLOBAL();
  (void) EXPECT_TRUE(true);
  (void) EXPECT_TRUE(CALL_BARE());
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
  (void) FORWARD_EXPRESSION(target());
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
}

#define CALL_DEFINED_IN_LIBRARY() target()
}

void outside_library()
{
  CALL_DEFINED_IN_LIBRARY();
}

#define BEGIN_CUDA_STD namespace cuda { namespace std {
#define END_CUDA_STD } }

BEGIN_CUDA_STD
void generated_namespace()
{
  target();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
}
END_CUDA_STD

// CHECK-FIXES-NOT: DiagnosticName:

// clang-format on
