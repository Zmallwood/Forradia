/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gen_rivers.hpp"
#include "theme_0/func/game_props.hpp"
#include "theme_0/func/world_struct/tile.hpp"
#include "theme_0/func/world_struct/world.hpp"
#include "theme_0/func/world_struct/world_area.hpp"

namespace forr {
  void gen_rivers() {
    auto w_area{_<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    auto scale{_<game_props>().k_world_scaling};
    auto num_rivers{20 * scale + rand_int(5 * scale)};
    for (auto i = 0; i < num_rivers; i++) {
      auto x{c_float(rand_int(sz.w))};
      auto y{c_float(rand_int(sz.h))};
      auto start_angle{rand_int(360)};
      auto len{45 + rand_int(20)};
      auto prev_x_coord{-1};
      auto prev_y_coord{-1};
      s_ptr<tile> prev_tl;
      for (auto j = 0; j < len; j++) {
        auto angle{start_angle + std::sin(j * M_PI / 10.0f) * 45};
        auto x_coord{c_int(x)};
        auto y_coord{c_int(y)};
        if (!w_area->is_valid_coord(x_coord, y_coord)) {
          continue;
        }
        auto tl = w_area->get_tl(x_coord, y_coord);
        if (tl && prev_tl) {
          // tile->SetGround("GroundWater");
          if (x_coord == prev_x_coord && y_coord > prev_y_coord) {
            prev_tl->set_river_dir_1(directions::south);
            tl->set_river_dir_2(directions::north);
          } else if (x_coord == prev_x_coord && y_coord < prev_y_coord) {
            prev_tl->set_river_dir_1(directions::north);
            tl->set_river_dir_2(directions::south);
          } else if (y_coord == prev_y_coord && x_coord > prev_x_coord) {
            prev_tl->set_river_dir_1(directions::east);
            tl->set_river_dir_2(directions::west);
          } else if (y_coord == prev_y_coord && x_coord < prev_x_coord) {
            prev_tl->set_river_dir_1(directions::west);
            tl->set_river_dir_2(directions::east);
          } else if (y_coord < prev_y_coord && x_coord > prev_x_coord) {
            prev_tl->set_river_dir_1(directions::north_east);
            tl->set_river_dir_2(directions::south_west);
          } else if (y_coord > prev_y_coord && x_coord > prev_x_coord) {
            prev_tl->set_river_dir_1(directions::south_east);
            tl->set_river_dir_2(directions::north_west);
          } else if (y_coord < prev_y_coord && x_coord < prev_x_coord) {
            prev_tl->set_river_dir_1(directions::north_west);
            tl->set_river_dir_2(directions::south_east);
          } else if (y_coord > prev_y_coord && x_coord < prev_x_coord) {
            prev_tl->set_river_dir_1(directions::south_west);
            tl->set_river_dir_2(directions::north_east);
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
        prev_tl = tl;
      }
    }
  }
}