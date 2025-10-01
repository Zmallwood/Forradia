/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_rock.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void GenerateRock() {
    auto worldArea{GetSingleton<world>().get_current_world_area()};
    auto size{worldArea->get_size()};
    auto scale{GetSingleton<game_properties>().k_worldScalingFactor};
    auto numRockAreas{30 + RandomInt(10)};
    for (auto i = 0; i < numRockAreas; i++) {
      auto xCenter{RandomInt(size.width)};
      auto yCenter{RandomInt(size.height)};
      auto radius{3 * scale + RandomInt(10 * scale)};
      for (auto y = yCenter - radius; y <= yCenter + radius; y++) {
        for (auto x = xCenter - radius; x <= xCenter + radius; x++) {
          if (!worldArea->is_valid_coordinate(x, y)) {
            continue;
          }
          auto dx{x - xCenter};
          auto dy{y - yCenter};
          if (dx * dx + dy * dy <= radius * radius) {
            auto tile{worldArea->get_tile(x, y)};
            if (tile->get_elevation() > 0) {
              tile->set_ground("GroundRock");
            }
          }
        }
      }
    }
  }
}