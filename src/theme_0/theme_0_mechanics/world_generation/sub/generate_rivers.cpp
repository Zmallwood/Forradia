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
  void generate_rivers() {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto size{worldArea->get_size()};
    auto scale{get_singleton<game_properties>().k_worldScalingFactor};
    auto numRivers{20 * scale + random_int(5 * scale)};
    for (auto i = 0; i < numRivers; i++) {
      auto x{c_float(random_int(size.width))};
      auto y{c_float(random_int(size.height))};
      auto startAngle{random_int(360)};
      auto length{45 + random_int(20)};
      auto prevXCoordinate{-1};
      auto prevYCoordinate{-1};
      s_ptr<tile> prevTile;
      for (auto j = 0; j < length; j++) {
        auto angle{startAngle + std::sin(j * M_PI / 10.0f) * 45};
        auto xCoordinate{c_int(x)};
        auto yCoordinate{c_int(y)};
        if (!worldArea->is_valid_coordinate(xCoordinate, yCoordinate)) {
          continue;
        }
        auto tile = worldArea->get_tile(xCoordinate, yCoordinate);
        if (tile && prevTile) {
          // tile->SetGround("GroundWater");
          if (xCoordinate == prevXCoordinate && yCoordinate > prevYCoordinate) {
            prevTile->set_river_direction_1(directions::South);
            tile->set_river_direction_2(directions::North);
          } else if (xCoordinate == prevXCoordinate &&
                     yCoordinate < prevYCoordinate) {
            prevTile->set_river_direction_1(directions::North);
            tile->set_river_direction_2(directions::South);
          } else if (yCoordinate == prevYCoordinate &&
                     xCoordinate > prevXCoordinate) {
            prevTile->set_river_direction_1(directions::East);
            tile->set_river_direction_2(directions::West);
          } else if (yCoordinate == prevYCoordinate &&
                     xCoordinate < prevXCoordinate) {
            prevTile->set_river_direction_1(directions::West);
            tile->set_river_direction_2(directions::East);
          } else if (yCoordinate < prevYCoordinate &&
                     xCoordinate > prevXCoordinate) {
            prevTile->set_river_direction_1(directions::NorthEast);
            tile->set_river_direction_2(directions::SouthWest);
          } else if (yCoordinate > prevYCoordinate &&
                     xCoordinate > prevXCoordinate) {
            prevTile->set_river_direction_1(directions::SouthEast);
            tile->set_river_direction_2(directions::NorthWest);
          } else if (yCoordinate < prevYCoordinate &&
                     xCoordinate < prevXCoordinate) {
            prevTile->set_river_direction_1(directions::NorthWest);
            tile->set_river_direction_2(directions::SouthEast);
          } else if (yCoordinate > prevYCoordinate &&
                     xCoordinate < prevXCoordinate) {
            prevTile->set_river_direction_1(directions::SouthWest);
            tile->set_river_direction_2(directions::NorthEast);
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