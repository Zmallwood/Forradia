/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_rivers.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void GenerateRivers() {
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};
    auto size{worldArea->GetSize()};
    auto scale{GetSingleton<GameProperties>().k_worldScalingFactor};
    auto numRivers{20 * scale + RandomInt(5 * scale)};
    for (auto i = 0; i < numRivers; i++) {
      auto x{CFloat(RandomInt(size.width))};
      auto y{CFloat(RandomInt(size.height))};
      auto startAngle{RandomInt(360)};
      auto length{45 + RandomInt(20)};
      auto prevXCoordinate{-1};
      auto prevYCoordinate{-1};
      SharedPtr<Tile> prevTile;
      for (auto j = 0; j < length; j++) {
        auto angle{startAngle + std::sin(j * M_PI / 10.0f) * 45};
        auto xCoordinate{CInt(x)};
        auto yCoordinate{CInt(y)};
        if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate)) {
          continue;
        }
        auto tile = worldArea->GetTile(xCoordinate, yCoordinate);
        if (tile && prevTile) {
          // tile->SetGround("GroundWater");
          if (xCoordinate == prevXCoordinate && yCoordinate > prevYCoordinate) {
            prevTile->SetRiverDirection1(Directions::South);
            tile->SetRiverDirection2(Directions::North);
          } else if (xCoordinate == prevXCoordinate &&
                     yCoordinate < prevYCoordinate) {
            prevTile->SetRiverDirection1(Directions::North);
            tile->SetRiverDirection2(Directions::South);
          } else if (yCoordinate == prevYCoordinate &&
                     xCoordinate > prevXCoordinate) {
            prevTile->SetRiverDirection1(Directions::East);
            tile->SetRiverDirection2(Directions::West);
          } else if (yCoordinate == prevYCoordinate &&
                     xCoordinate < prevXCoordinate) {
            prevTile->SetRiverDirection1(Directions::West);
            tile->SetRiverDirection2(Directions::East);
          } else if (yCoordinate < prevYCoordinate &&
                     xCoordinate > prevXCoordinate) {
            prevTile->SetRiverDirection1(Directions::NorthEast);
            tile->SetRiverDirection2(Directions::SouthWest);
          } else if (yCoordinate > prevYCoordinate &&
                     xCoordinate > prevXCoordinate) {
            prevTile->SetRiverDirection1(Directions::SouthEast);
            tile->SetRiverDirection2(Directions::NorthWest);
          } else if (yCoordinate < prevYCoordinate &&
                     xCoordinate < prevXCoordinate) {
            prevTile->SetRiverDirection1(Directions::NorthWest);
            tile->SetRiverDirection2(Directions::SouthEast);
          } else if (yCoordinate > prevYCoordinate &&
                     xCoordinate < prevXCoordinate) {
            prevTile->SetRiverDirection1(Directions::SouthWest);
            tile->SetRiverDirection2(Directions::NorthEast);
          }
        }
        // if (xCoordinate != prevXCoordinate && yCoordinate != prevYCoordinate
        // && prevXCoordinate != -1 && prevYCoordinate != -1)
        // {
        //     if (xCoordinate < prevXCoordinate)
        //     {
        //         auto tileAdjacentEast{worldArea->GetTile(xCoordinate + 1,
        //         yCoordinate)};
        //         if (tileAdjacentEast)
        //         {
        //             tileAdjacentEast->SetGround("GroundWater");
        //         }
        //     }
        //     else
        //     {
        //         auto tileAdjacentWest{worldArea->GetTile(xCoordinate - 1,
        //         yCoordinate)};
        //         if (tileAdjacentWest)
        //         {
        //             tileAdjacentWest->SetGround("GroundWater");
        //         }
        //     }
        // }
        auto dx = std::cos(angle * M_PI / 180.0f);
        auto dy = std::sin(angle * M_PI / 180.0f);
        x += dx;
        y += dy;
        prevXCoordinate = xCoordinate;
        prevYCoordinate = yCoordinate;
        prevTile = tile;
      }
    }
  }
}