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
  void GenerateGrass() {
    auto worldArea{GetSingleton<world>().GetCurrentWorldArea()};
    auto size{worldArea->GetSize()};
    auto scale{GetSingleton<game_properties>().k_worldScalingFactor};
    auto numGrassAreas{50 + RandomInt(20)};
    for (auto i = 0; i < numGrassAreas; i++) {
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
            tile->SetGround("GroundGrass");
          }
        }
      }
    }
  }
}