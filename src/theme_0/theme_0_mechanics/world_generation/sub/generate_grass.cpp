/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_grass.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_grass() {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto size{worldArea->get_size()};
    auto scale{get_singleton<game_properties>().k_worldScalingFactor};
    auto numGrassAreas{50 + random_int(20)};
    for (auto i = 0; i < numGrassAreas; i++) {
      auto xCenter{random_int(size.width)};
      auto yCenter{random_int(size.height)};
      auto radius{3 * scale + random_int(10 * scale)};
      for (auto y = yCenter - radius; y <= yCenter + radius; y++) {
        for (auto x = xCenter - radius; x <= xCenter + radius; x++) {
          if (!worldArea->is_valid_coordinate(x, y)) {
            continue;
          }
          auto dx{x - xCenter};
          auto dy{y - yCenter};
          if (dx * dx + dy * dy <= radius * radius) {
            auto tile{worldArea->get_tile(x, y)};
            tile->set_ground("GroundGrass");
          }
        }
      }
    }
  }
}