| Proposal ID      |                                                                                  |
| ---------------- | -------------------------------------------------------------------------------- |
| Name             | SYCL interoperability scope                                                      |
| Date of Creation | 10 June 2022                                                                     |
| Target           | SYCL Next                                                                        |
| Current Status   | _Draft_                                                                          |
| Reply-to         | Nicolas Miller <nicolas.miller@codeplay.com>                                     |
| Original author  | Nicolas Miller <nicolas.miller@codeplay.com>                                     |
| Contributors     | Tadej Ciglaric <tadej.ciglaric@codeplay.com>, Gordon Brown <gordon@codeplay.com> |

# SYCL interoperability scope

The SYCL 2020 specification provides an API to create SYCL objects from backend
specific handles and to get backend specific handles from SYCL objects for
interoperability purposes.

However the SYCL 2020 specification doesn't clearly define the lifetime of SYCL
objects, most of the SYCL objects have reference semantics and may be kept alive
by the SYCL runtime even if the associated SYCL user objects have been deleted.

This is problematic for interoperability, because it means that as long as
a native backend object has been tied to a SYCL object at some point, there is
no way for the user to know if the SYCL runtime is really done with this handle.

And so this raises the question of ownership of native backend handles, question
which is not addressed by the SYCL specification and left to backend
specification. For some backends such as the OpenCL backend which uses reference
counting for the backend objects this is not an issue, however for other
backends there is currently no good solution to handle this.

Thus, this proposal aims to solve this ownership issue by modifying existing
interfaces and adding new alternatives.

There are three main parts of this proposal:

* Removal of the `get_native` interface. There is currently no way to know when
  a handle returned from that interface can be safely used. The `host_task`
  interoperability should be used instead to access backend objects from SYCL
  objects.
* Mandate that the `make_{SYCL object}` interface takes ownership of passed in
  backend objects. This means that a user may not use a native backend object
  after it has been turned into a SYCL object, and the SYCL runtime is
  responsible for cleaning up the native handle.
* Introduce an `interop_scope` interface, this interface provides a scoped
  environment in which SYCL objects may be created from native backend objects
  and used, however these SYCL objects are guaranteed to have limited lifetime,
  and the native backend objects can thus be used again by the user once the
  `interop_scope` has finished executing.

## Overview of `interop_scope`

```cpp
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
```
