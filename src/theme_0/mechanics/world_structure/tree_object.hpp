/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "object.hpp"

namespace forr {
  class tree_object : public object {
   public:
    tree_object(str_view obj_type_name) : object(obj_type_name) {
      init(obj_type_name);
    }

    auto get_trunk_parts() const { return m_trunk_parts; }

    auto get_needle_types() const { return m_needle_types; }

    auto get_w_factor() const { return m_w_factor; }

   private:
    void init(str_view obj_type_name);

    vec<point_f> m_trunk_parts;
    vec<int> m_needle_types;
    float m_w_factor{1.0f};
  };
}