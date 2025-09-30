/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateGrass.hpp"
#include "Theme0/Theme0Mechanics/Configuration/GameProperties.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"

namespace Forradia {
  void GenerateRock() {
    auto worldArea{_<World>().GetCurrentWorldArea()};

    auto size{worldArea->GetSize()};

    auto scale{_<GameProperties>().k_worldScalingFactor};

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