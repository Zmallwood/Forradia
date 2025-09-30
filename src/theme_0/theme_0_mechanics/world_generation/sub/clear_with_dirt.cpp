/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "clear_with_dirt.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace Forradia {
  void ClearWithDirt() {
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};
    auto size{worldArea->GetSize()};
    size.width *= GetSingleton<GameProperties>().k_worldScalingFactor;
    size.height *= GetSingleton<GameProperties>().k_worldScalingFactor;
    for (auto y = 0; y < size.height; y++) {
      for (auto x = 0; x < size.width; x++) {
        auto tile{worldArea->GetTile(x, y)};
        if (tile) {
          tile->SetGround("GroundDirt");
        }
      }
    }
  }
}