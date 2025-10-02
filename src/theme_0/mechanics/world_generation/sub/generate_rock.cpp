/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_rock.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_rock() {
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto size{world_area->get_size()};
    auto scale{get_singleton<game_properties>().k_world_scaling_factor};
    auto num_rock_areas{30 + random_int(10)};
    for (auto i = 0; i < num_rock_areas; i++) {
      auto x_center{random_int(size.w)};
      auto y_center{random_int(size.h)};
      auto radius{3 * scale + random_int(10 * scale)};
      for (auto y = y_center - radius; y <= y_center + radius; y++) {
        for (auto x = x_center - radius; x <= x_center + radius; x++) {
          if (!world_area->is_valid_coordinate(x, y)) {
            continue;
          }
          auto dx{x - x_center};
          auto dy{y - y_center};
          if (dx * dx + dy * dy <= radius * radius) {
            auto tile{world_area->get_tile(x, y)};
            if (tile->get_elevation() > 0) {
              tile->set_ground("GroundRock");
            }
          }
        }
      }
    }
  }
}