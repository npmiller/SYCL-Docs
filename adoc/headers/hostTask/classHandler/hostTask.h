// Copyright (c) 2011-2022 The Khronos Group, Inc.
// SPDX-License-Identifier: MIT

class handler {
  ...

 public:
  template <typename T>
  void sync_host_task(T &&hostTaskCallable); // (1)
                                             //
  template <typename T>
  void async_host_task(T &&hostTaskCallable); // (2)

  ...
};
