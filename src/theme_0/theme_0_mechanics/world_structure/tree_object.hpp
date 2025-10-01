/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "object.hpp"

namespace forr {
  class tree_object : public object {
  public:
    tree_object(str_view objectTypeName) : object(objectTypeName) {
      initialize(objectTypeName);
    }

    auto get_trunk_parts() const { return m_trunkParts; }

    auto get_needle_types() const { return m_needleTypes; }

    auto get_width_factor() const { return m_widthFactor; }

  private:
    void initialize(str_view objectTypeName);

    vec<point_f> m_trunkParts;
    vec<int> m_needleTypes;
    float m_widthFactor{1.0f};
  };
}