/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class object {
  public:
    object(str_view objectTypeName) : m_type(hash(objectTypeName)) {}

    auto get_type() const { return m_type; }

  private:
    int m_type{0};
  };
}