/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  // A set of aliases for commonly used types.
  using str = std::string;
  using str_view = std::string_view;
  template <class T> using s_ptr= std::shared_ptr<T>;
  template <class T> using vec = std::vector<T>;
  template <class T> using func = std::function<T>;
}