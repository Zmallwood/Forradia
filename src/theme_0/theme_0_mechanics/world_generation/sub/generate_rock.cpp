/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "generate_rock.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace Forradia {
  void GenerateRock() {
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};
    auto size{worldArea->GetSize()};
    auto scale{GetSingleton<GameProperties>().k_worldScalingFactor};
    auto numRockAreas{30 + RandomInt(10)};
    for (auto i = 0; i < numRockAreas; i++) {
      auto xCenter{RandomInt(size.width)};
      auto yCenter{RandomInt(size.height)};
      auto radius{3 * scale + RandomInt(10 * scale)};
      for (auto y = yCenter - radius; y <= yCenter + radius; y++) {
        for (auto x = xCenter - radius; x <= xCenter + radius; x++) {
          if (!worldArea->IsValidCoordinate(x, y)) {
            continue;
          }
          auto dx{x - xCenter};
          auto dy{y - yCenter};
          if (dx * dx + dy * dy <= radius * radius) {
            auto tile{worldArea->GetTile(x, y)};
            if (tile->GetElevation() > 0) {
              tile->SetGround("GroundRock");
            }
          }
        }
      }
    }
  }
}