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
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};
    auto size{worldArea->GetSize()};
    auto scale{GetSingleton<GameProperties>().k_worldScalingFactor};
    auto numHills{140 + RandomInt(30)};
    for (auto i = 0; i < numHills; i++) {
      auto xCenter{RandomInt(size.width)};
      auto yCenter{RandomInt(size.height)};
      auto maxRadius{5 * scale + RandomInt(5 * scale)};
      for (auto r = maxRadius; r >= 0; r--) {
        for (auto y = yCenter - r; y <= yCenter + r; y++) {
          for (auto x = xCenter - r; x <= xCenter + r; x++) {
            if (!worldArea->IsValidCoordinate(x, y)) {
              continue;
            }
            auto dx{x - xCenter};
            auto dy{y - yCenter};
            if (dx * dx + dy * dy <= r * r) {
              auto tile{worldArea->GetTile(x, y)};
              if (tile && tile->GetGround() != Hash("GroundWater")) {
                auto tileN{worldArea->GetTile(x, y - 1)};
                auto tileS{worldArea->GetTile(x, y + 1)};
                auto tileW{worldArea->GetTile(x - 1, y)};
                auto tileE{worldArea->GetTile(x + 1, y)};
                auto tileNW{worldArea->GetTile(x - 1, y - 1)};
                auto tileNE{worldArea->GetTile(x + 1, y - 1)};
                auto tileSW{worldArea->GetTile(x - 1, y + 1)};
                auto tileSE{worldArea->GetTile(x + 1, y + 1)};
                if ((tileN && tileN->GetGround() == Hash("GroundWater")) ||
                    (tileS && tileS->GetGround() == Hash("GroundWater")) ||
                    (tileW && tileW->GetGround() == Hash("GroundWater")) ||
                    (tileE && tileE->GetGround() == Hash("GroundWater")) ||
                    (tileNW && tileNW->GetGround() == Hash("GroundWater")) ||
                    (tileNE && tileNE->GetGround() == Hash("GroundWater")) ||
                    (tileSW && tileSW->GetGround() == Hash("GroundWater")) ||
                    (tileSE && tileSE->GetGround() == Hash("GroundWater"))) {
                  continue;
                }
                if (tileN && tileN->GetElevation() < tile->GetElevation()) {
                  continue;
                }
                if (tileS && tileS->GetElevation() < tile->GetElevation()) {
                  continue;
                }
                if (tileW && tileW->GetElevation() < tile->GetElevation()) {
                  continue;
                }
                if (tileE && tileE->GetElevation() < tile->GetElevation()) {
                  continue;
                }
                if (tileNW && tileNW->GetElevation() < tile->GetElevation()) {
                  continue;
                }
                if (tileNE && tileNE->GetElevation() < tile->GetElevation()) {
                  continue;
                }
                if (tileSW && tileSW->GetElevation() < tile->GetElevation()) {
                  continue;
                }
                if (tileSE && tileSE->GetElevation() < tile->GetElevation()) {
                  continue;
                }
                tile->SetElevation(tile->GetElevation() + 1);
              }
            }
          }
        }
      }
    }
  }
}