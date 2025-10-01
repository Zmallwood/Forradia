/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class Object {
  public:
    Object(str_view objectTypeName) : m_type(Hash(objectTypeName)) {}

    auto GetType() const { return m_type; }

  private:
    int m_type{0};
  };
}