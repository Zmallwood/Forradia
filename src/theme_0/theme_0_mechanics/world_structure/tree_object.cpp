/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tree_object.hpp"

namespace forr {
  void tree_object::initialize(str_view object_type_name) {
    if (object_type_name != "ObjectFirTree" &&
        object_type_name != "ObjectBirchTree") {
      return;
    }
    int num_trunk_parts;
    if (object_type_name == "ObjectFirTree") {
      num_trunk_parts = 55 + random_int(44);
    } else if (object_type_name == "ObjectBirchTree") {
      num_trunk_parts = 25 + random_int(14);
    }
    m_width_factor *= (random_int(5) + 1) / 2.0f + 1.0f;
    auto offset_x{0.0f};
    for (auto i = 0; i < num_trunk_parts; i++) {
      offset_x += (random_int(20) - 10) / 100.0f;
      auto offset_y{i * 0.1f};
      auto position{point_f{offset_x, offset_y}};
      auto needles_type{random_int(5)};
      m_trunk_parts.push_back(position);
      str needles_name;
      if (object_type_name == "ObjectFirTree") {
        needles_name = "ObjectFirTreeNeedles";
      } else if (object_type_name == "ObjectBirchTree") {
        if (i % 4 != 0) {
          m_needle_types.push_back(0);
          continue;
        }
        needles_name = "ObjectBirchTreeBranch";
      }
      m_needle_types.push_back(
          needles_type ? hash(needles_name + std::to_string(needles_type)) : 0);
    }
  }
}