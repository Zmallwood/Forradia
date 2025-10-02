/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_hovering.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"
#include "theme_0/theme_0_mechanics/math/tile_grid_math.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void tile_hovering::update() {
    auto player_position{get_singleton<player>().get_position()};
    auto mouse_position{get_normalized_mouse_position()};
    auto tile_size{calculate_tile_size()};
    auto screen_relative_x{c_int(mouse_position.x / tile_size.w)};
    auto grid_size{calculate_grid_size()};
    auto hovered_x_coord{player_position.x - (grid_size.w - 1) / 2 +
                         screen_relative_x};
    auto screen_relative_x_px{
        (hovered_x_coord - (player_position.x - (grid_size.w - 1) / 2)) *
        tile_size.w};
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto extra_rows{8};
    auto top_y_coord{c_int(player_position.y - (grid_size.h - 1) / 2) -
                     extra_rows};
    auto player_tile{world_area->get_tile(player_position)};
    auto player_elev{
        player_tile ? world_area->get_tile(player_position)->get_elevation()
                    : 0};
    auto screen_relative_y_px{-extra_rows * tile_size.h};
    for (auto y = -extra_rows; y < grid_size.h + extra_rows; y++) {
      auto y_coord{c_int(player_position.y - (grid_size.h - 1) / 2 + y)};
      auto coord{point{hovered_x_coord, y_coord}};
      auto tile{world_area->get_tile(coord)};
      if (!tile) {
        screen_relative_y_px = 0.5f +
                               (y - (grid_size.h - 1) / 2) * tile_size.h +
                               player_elev * tile_size.h / 2;
        continue;
      }
      auto elev{tile->get_elevation()};
      screen_relative_y_px = 0.5f + (y - (grid_size.h - 1) / 2) * tile_size.h +
                             (player_elev - elev) * tile_size.h / 2;
      auto coord_nw{point{coord.x, coord.y}};
      auto coord_ne{point{coord.x + 1, coord.y}};
      auto coord_sw{point{coord.x, coord.y + 1}};
      auto coord_se{point{coord.x + 1, coord.y + 1}};
      if (!world_area->is_valid_coordinate(coord_nw.x, coord_nw.y) ||
          !world_area->is_valid_coordinate(coord_ne.x, coord_ne.y) ||
          !world_area->is_valid_coordinate(coord_sw.x, coord_sw.y) ||
          !world_area->is_valid_coordinate(coord_se.x, coord_se.y)) {
        continue;
      }
      auto tile_nw{world_area->get_tile(coord_nw)};
      auto tile_ne{world_area->get_tile(coord_ne)};
      auto tile_sw{world_area->get_tile(coord_sw)};
      auto tile_se{world_area->get_tile(coord_se)};
      if (!tile_nw || !tile_ne || !tile_se || !tile_sw) {
        continue;
      }
      float local_tile_height;
      if (tile_nw->get_elevation() > tile_sw->get_elevation() &&
          tile_ne->get_elevation() > tile_se->get_elevation()) {
        local_tile_height = tile_size.h * 1.5f;
      } else if (tile_nw->get_elevation() < tile_sw->get_elevation() &&
                 tile_ne->get_elevation() < tile_se->get_elevation()) {
        local_tile_height = tile_size.h * 0.5f;
      } else if (tile_ne->get_elevation() > tile_nw->get_elevation() &&
                 tile_se->get_elevation() > tile_sw->get_elevation()) {
        local_tile_height = tile_size.h * 1.5f;
      } else if (tile_nw->get_elevation() > tile_ne->get_elevation() &&
                 tile_sw->get_elevation() > tile_se->get_elevation()) {
        local_tile_height = tile_size.h * 1.5f;
      } else if (tile_nw->get_elevation() > tile_ne->get_elevation() &&
                 tile_nw->get_elevation() > tile_se->get_elevation() &&
                 tile_nw->get_elevation() > tile_sw->get_elevation()) {
        local_tile_height = tile_size.h * 1.5f;
      } else if (tile_ne->get_elevation() > tile_nw->get_elevation() &&
                 tile_ne->get_elevation() > tile_se->get_elevation() &&
                 tile_ne->get_elevation() > tile_sw->get_elevation()) {
        local_tile_height = tile_size.h * 1.5f;
      } else if (tile_sw->get_elevation() > tile_nw->get_elevation() &&
                 tile_sw->get_elevation() > tile_se->get_elevation() &&
                 tile_sw->get_elevation() > tile_ne->get_elevation()) {
        local_tile_height = tile_size.h * 1.0f;
      } else if (tile_se->get_elevation() > tile_nw->get_elevation() &&
                 tile_se->get_elevation() > tile_ne->get_elevation() &&
                 tile_se->get_elevation() > tile_sw->get_elevation()) {
        local_tile_height = tile_size.h * 1.0f;
      } else if (tile_sw->get_elevation() < tile_nw->get_elevation() &&
                 tile_sw->get_elevation() < tile_ne->get_elevation() &&
                 tile_sw->get_elevation() < tile_se->get_elevation()) {
        local_tile_height = tile_size.h * 1.5f;
      } else if (tile_se->get_elevation() < tile_nw->get_elevation() &&
                 tile_se->get_elevation() < tile_ne->get_elevation() &&
                 tile_se->get_elevation() < tile_sw->get_elevation()) {
        local_tile_height = tile_size.h * 1.5f;
      } else if (tile_nw->get_elevation() < tile_ne->get_elevation() &&
                 tile_nw->get_elevation() < tile_sw->get_elevation() &&
                 tile_nw->get_elevation() < tile_se->get_elevation()) {
        local_tile_height = tile_size.h * 1.0f;
      } else if (tile_ne->get_elevation() < tile_nw->get_elevation() &&
                 tile_ne->get_elevation() < tile_sw->get_elevation() &&
                 tile_ne->get_elevation() < tile_se->get_elevation()) {
        local_tile_height = tile_size.h * 1.0f;
      } else if (tile_sw->get_elevation() == tile_ne->get_elevation() &&
                 tile_nw->get_elevation() < tile_sw->get_elevation() &&
                 tile_se->get_elevation() < tile_sw->get_elevation()) {
        local_tile_height = tile_size.h * 1.5f;
      } else if (tile_nw->get_elevation() == tile_se->get_elevation() &&
                 tile_ne->get_elevation() < tile_nw->get_elevation() &&
                 tile_sw->get_elevation() < tile_nw->get_elevation()) {
        local_tile_height = tile_size.h * 1.5f;
      } else {
        local_tile_height = tile_size.h;
      }
      auto rect{rect_f{screen_relative_x_px,
                       screen_relative_y_px - local_tile_height / 2,
                       tile_size.w, local_tile_height}};
      if (rect.contains(mouse_position)) {
        m_hovered_coordinate = {hovered_x_coord, y_coord};
        return;
      }
    }
  }
}