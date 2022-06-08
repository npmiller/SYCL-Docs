// Copyright (c) 2011-2021 The Khronos Group, Inc.
// SPDX-License-Identifier: MIT

template <backend Backend>
std::vector<backend_return_t<Backend, event>> get_native_events() const; // (1)
                                                                         //

template <backend Backend>
void add_events(std::vector<backend_return_t<Backend, event>>) const; // (2)
                                                                      //
