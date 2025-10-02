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
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto size{world_area->get_size()};
    auto scale{get_singleton<game_properties>().k_world_scaling_factor};
    auto num_rivers{20 * scale + random_int(5 * scale)};
    for (auto i = 0; i < num_rivers; i++) {
      auto x{c_float(random_int(size.w))};
      auto y{c_float(random_int(size.h))};
      auto start_angle{random_int(360)};
      auto length{45 + random_int(20)};
      auto prev_x_coord{-1};
      auto prev_y_coord{-1};
      s_ptr<tile> prev_tile;
      for (auto j = 0; j < length; j++) {
        auto angle{start_angle + std::sin(j * M_PI / 10.0f) * 45};
        auto x_coord{c_int(x)};
        auto y_coord{c_int(y)};
        if (!world_area->is_valid_coordinate(x_coord, y_coord)) {
          continue;
        }
        auto tile = world_area->get_tile(x_coord, y_coord);
        if (tile && prev_tile) {
          // tile->SetGround("GroundWater");
          if (x_coord == prev_x_coord && y_coord > prev_y_coord) {
            prev_tile->set_river_direction_1(directions::south);
            tile->set_river_direction_2(directions::north);
          } else if (x_coord == prev_x_coord && y_coord < prev_y_coord) {
            prev_tile->set_river_direction_1(directions::north);
            tile->set_river_direction_2(directions::south);
          } else if (y_coord == prev_y_coord && x_coord > prev_x_coord) {
            prev_tile->set_river_direction_1(directions::east);
            tile->set_river_direction_2(directions::west);
          } else if (y_coord == prev_y_coord && x_coord < prev_x_coord) {
            prev_tile->set_river_direction_1(directions::west);
            tile->set_river_direction_2(directions::east);
          } else if (y_coord < prev_y_coord && x_coord > prev_x_coord) {
            prev_tile->set_river_direction_1(directions::north_east);
            tile->set_river_direction_2(directions::south_west);
          } else if (y_coord > prev_y_coord && x_coord > prev_x_coord) {
            prev_tile->set_river_direction_1(directions::south_east);
            tile->set_river_direction_2(directions::north_west);
          } else if (y_coord < prev_y_coord && x_coord < prev_x_coord) {
            prev_tile->set_river_direction_1(directions::north_west);
            tile->set_river_direction_2(directions::south_east);
          } else if (y_coord > prev_y_coord && x_coord < prev_x_coord) {
            prev_tile->set_river_direction_1(directions::south_west);
            tile->set_river_direction_2(directions::north_east);
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
        prev_x_coord = x_coord;
        prev_y_coord = y_coord;
        prev_tile = tile;
      }
    }
  }
}