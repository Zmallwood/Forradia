/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gen_grass.hpp"
#include "theme_0/func/configuration/game_properties.hpp"
#include "theme_0/func/world_structure/tile.hpp"
#include "theme_0/func/world_structure/world.hpp"
#include "theme_0/func/world_structure/world_area.hpp"

namespace forr {
  void gen_grass() {
    auto w_area{get_ston<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    auto scale{get_ston<game_properties>().k_world_scaling};
    auto num_grass_areas{50 + rand_int(20)};
    for (auto i = 0; i < num_grass_areas; i++) {
      auto x_cent{rand_int(sz.w)};
      auto y_cent{rand_int(sz.h)};
      auto r{3 * scale + rand_int(10 * scale)};
      for (auto y = y_cent - r; y <= y_cent + r; y++) {
        for (auto x = x_cent - r; x <= x_cent + r; x++) {
          if (!w_area->is_valid_coord(x, y)) {
            continue;
          }
          auto dx{x - x_cent};
          auto dy{y - y_cent};
          if (dx * dx + dy * dy <= r * r) {
            auto tl{w_area->get_tl(x, y)};
            tl->set_ground("GroundGrass");
          }
        }
      }
    }
  }
}