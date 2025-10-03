/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tree_object.hpp"

namespace forr {
  void tree_object::init(str_view obj_type_name) {
    if (obj_type_name != "ObjectFirTree" &&
        obj_type_name != "ObjectBirchTree") {
      return;
    }
    int num_trunk_parts;
    if (obj_type_name == "ObjectFirTree") {
      num_trunk_parts = 55 + rand_int(44);
    } else if (obj_type_name == "ObjectBirchTree") {
      num_trunk_parts = 25 + rand_int(14);
    }
    m_w_factor *= (rand_int(5) + 1) / 2.0f + 1.0f;
    auto offs_x{0.0f};
    for (auto i = 0; i < num_trunk_parts; i++) {
      offs_x += (rand_int(20) - 10) / 100.0f;
      auto offset_y{i * 0.1f};
      auto pos{point_f{offs_x, offset_y}};
      auto needles_type{rand_int(5)};
      m_trunk_parts.push_back(pos);
      str needles_name;
      if (obj_type_name == "ObjectFirTree") {
        needles_name = "ObjectFirTreeNeedles";
      } else if (obj_type_name == "ObjectBirchTree") {
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