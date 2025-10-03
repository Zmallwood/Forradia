/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_grass.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_grass() {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto sz{w_area->get_size()};
    auto scale{get_singleton<game_properties>().k_world_scaling};
    auto num_grass_areas{50 + random_int(20)};
    for (auto i = 0; i < num_grass_areas; i++) {
      auto x_cent{random_int(sz.w)};
      auto y_cent{random_int(sz.h)};
      auto r{3 * scale + random_int(10 * scale)};
      for (auto y = y_cent - r; y <= y_cent + r; y++) {
        for (auto x = x_cent - r; x <= x_cent + r; x++) {
          if (!w_area->is_valid_coordinate(x, y)) {
            continue;
          }
          auto dx{x - x_cent};
          auto dy{y - y_cent};
          if (dx * dx + dy * dy <= r * r) {
            auto tl{w_area->get_tile(x, y)};
            tl->set_ground("GroundGrass");
          }
        }
      }
    }
  }
}