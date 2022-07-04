// Copyright (c) 2011-2022 The Khronos Group, Inc.
// SPDX-License-Identifier: MIT

namespace sycl {

template <backend Backend>
class interop_scope_handle {
 private:

  interop_scope_handle(__unspecified__);

 public:

  interop_scope_handle() = delete;

  backend get_backend() const noexcept;

  template <typename DataT, int Dims>
  buffer<DataT, Dims>
      get_buffer(backend_return_t<Backend, buffer<DataT, Dims>>);

  template <int Dims>
  sampled_image<Dims>
      get_image(backend_return_t<Backend, sampled_image<DataT, Dims>>);

  template <int Dims>
  unsampled_image<Dims>
      get_image(backend_return_t<Backend, unsampled_image<DataT, Dims>>);

  event get_event(backend_return_t<Backend, event>);

  platform get_platform(backend_return_t<Backend, platform>);

  device get_device(backend_return_t<Backend, device>);

  context get_context(backend_return_t<Backend, context>);

  queue get_queue(backend_return_t<Backend, queue>);
};

template <backend Backend, typename T>
backend_return_t<Backend, event> interop_scope(T &&interopScopeCallable);

}  // namespace sycl
