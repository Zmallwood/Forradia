/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_elevation.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void GenerateElevation() {
    auto worldArea{GetSingleton<world>().get_current_world_area()};
    auto size{worldArea->get_size()};
    auto scale{GetSingleton<game_properties>().k_worldScalingFactor};
    auto numHills{140 + RandomInt(30)};
    for (auto i = 0; i < numHills; i++) {
      auto xCenter{RandomInt(size.width)};
      auto yCenter{RandomInt(size.height)};
      auto maxRadius{5 * scale + RandomInt(5 * scale)};
      for (auto r = maxRadius; r >= 0; r--) {
        for (auto y = yCenter - r; y <= yCenter + r; y++) {
          for (auto x = xCenter - r; x <= xCenter + r; x++) {
            if (!worldArea->is_valid_coordinate(x, y)) {
              continue;
            }
            auto dx{x - xCenter};
            auto dy{y - yCenter};
            if (dx * dx + dy * dy <= r * r) {
              auto tile{worldArea->get_tile(x, y)};
              if (tile && tile->get_ground() != Hash("GroundWater")) {
                auto tileN{worldArea->get_tile(x, y - 1)};
                auto tileS{worldArea->get_tile(x, y + 1)};
                auto tileW{worldArea->get_tile(x - 1, y)};
                auto tileE{worldArea->get_tile(x + 1, y)};
                auto tileNW{worldArea->get_tile(x - 1, y - 1)};
                auto tileNE{worldArea->get_tile(x + 1, y - 1)};
                auto tileSW{worldArea->get_tile(x - 1, y + 1)};
                auto tileSE{worldArea->get_tile(x + 1, y + 1)};
                if ((tileN && tileN->get_ground() == Hash("GroundWater")) ||
                    (tileS && tileS->get_ground() == Hash("GroundWater")) ||
                    (tileW && tileW->get_ground() == Hash("GroundWater")) ||
                    (tileE && tileE->get_ground() == Hash("GroundWater")) ||
                    (tileNW && tileNW->get_ground() == Hash("GroundWater")) ||
                    (tileNE && tileNE->get_ground() == Hash("GroundWater")) ||
                    (tileSW && tileSW->get_ground() == Hash("GroundWater")) ||
                    (tileSE && tileSE->get_ground() == Hash("GroundWater"))) {
                  continue;
                }
                if (tileN && tileN->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tileS && tileS->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tileW && tileW->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tileE && tileE->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tileNW && tileNW->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tileNE && tileNE->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tileSW && tileSW->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                if (tileSE && tileSE->get_elevation() < tile->get_elevation()) {
                  continue;
                }
                tile->set_elevation(tile->get_elevation() + 1);
              }
            }
          }
        }
      }
    }
  }
}