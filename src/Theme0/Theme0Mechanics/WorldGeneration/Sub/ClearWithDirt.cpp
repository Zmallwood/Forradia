/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "ClearWithDirt.hpp"
#include "Theme0/Theme0Mechanics/Configuration/GameProperties.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"

namespace Forradia {
  void ClearWithDirt() {
    auto worldArea{_<World>().GetCurrentWorldArea()};

    auto size{worldArea->GetSize()};

    size.width *= _<GameProperties>().k_worldScalingFactor;
    size.height *= _<GameProperties>().k_worldScalingFactor;

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