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
template <class T>
struct external
{
  static void call();
  template <class U>
  struct rebind
  {
    static void call();
  };
};
}

namespace cub
{
template <class T>
struct local
{
  static void call();
  template <class U>
  struct rebind
  {
    static void call();
  };
};

template <class Traits>
struct view
{
  using traits_type = Traits;
  void operations(const char* text)
  {
    traits_type::length(text);
    Traits::eq('a', 'b');
  }
};

template <class T>
using parameter_alias = T;

template <class T>
void dependent_parameters()
{
  T::call();
  parameter_alias<T>::call();
  using nested_alias = typename T::nested_type;
  nested_alias::call();
  T::nested_type::call();
  T::template rebind<int>::call();
  T::nested_type::template rebind<int>::call();
  T::nested_type::template rebind<int>::nested_type::call();
  using deep_alias = typename T::nested_type::template rebind<int>::nested_type;
  deep_alias::call();
}

template <class T>
void local_specializations()
{
  local<T>::call();
  local<T>::template rebind<int>::call();
  local<T>::template rebind<int>::nested_type::template rebind<double>::call();
  local<T>::template rebind<typename T::nested_type>::call();
}

template <class T>
void external_specializations()
{
  other_ns::external<T>::call();
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
  other_ns::external<T>::template rebind<int>::call();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
  other_ns::external<typename T::nested_type>::call();
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
  other_ns::external<typename T::nested_type>::template rebind<int>::nested_type::call();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
  other_ns::external<local<T>>::call();
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
  ::other_ns::external<T>::call();
  ::other_ns::external<T>::template rebind<int>::call();
}

template <class T>
using external_alias = ::other_ns::external<T>;

template <class T>
void aliases()
{
  external_alias<T>::call();
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
  using external_nested = typename other_ns::external<T>::template rebind<int>::nested_type;
  external_nested::call();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
}

template <>
struct local<int> : other_ns::external<int>
{};

template <class T>
void inherited_templates()
{
  local<int>::template rebind<T>::call();
  // CHECK-MESSAGES: :[[@LINE-1]]:{{[0-9]+}}: warning: {{.*}} [cccl-qualified-call]
  // CHECK-FIXES-LABEL: - DiagnosticName: cccl-qualified-call
  // CHECK-FIXES: Replacements: []
  // CHECK-FIXES-NOT: Message: 'Call appears to originate from namespace
  // CHECK-MESSAGES-NOT: {{:[0-9]+:[0-9]+: warning:}}
  // CHECK-MESSAGES-NOT: note: Call appears to originate from namespace
}

template <template <class> class Container, class T>
void template_template_parameter()
{
  Container<T>::call();
}
}

namespace cub
{
void target();

template <class T>
void function()
{
  target();
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

template <class T>
struct wrapper
{
  void member()
  {
    target();
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

  static void static_member()
  {
    target();
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
};

template <>
void function<char>()
{
  target();
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

template <class T>
struct wrapper<T*>
{
  void member()
  {
    target();
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
};

// Instantiation must not duplicate diagnostics from the template definition.
void instantiate(wrapper<int>& integer, wrapper<double>& floating, wrapper<int*>& pointer)
{
  ::cub::function<int>();
  ::cub::function<double>();
  ::cub::function<char>();
  integer.member();
  floating.member();
  pointer.member();
  ::cub::wrapper<int>::static_member();
}

template void function<long>();
}

// CHECK-FIXES-NOT: DiagnosticName:

// clang-format on
