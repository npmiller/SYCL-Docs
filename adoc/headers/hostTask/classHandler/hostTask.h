// Copyright (c) 2011-2022 The Khronos Group, Inc.
// SPDX-License-Identifier: MIT

class handler {
  ...

 public:
  template <typename T>
  void host_task(T &&hostTaskCallable, const property_list &propList = {}); // (1)
                                                                            //
  ...
};
