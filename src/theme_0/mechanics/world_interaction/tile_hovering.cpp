/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_hovering.hpp"
#include "theme_0/mechanics/core_game_objects/player.hpp"
#include "theme_0/mechanics/math/tile_grid_math.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void tile_hovering::update() {
    auto player_pos{get_ston<player>().get_position()};
    auto mouse_pos{get_norm_mouse_pos()};
    auto tl_sz{calculate_tile_size()};
    auto screen_rel_x{c_int(mouse_pos.x / tl_sz.w)};
    auto grid_sz{calculate_grid_size()};
    auto hovered_x_coord{player_pos.x - (grid_sz.w - 1) / 2 + screen_rel_x};
    auto screen_rel_x_px{
        (hovered_x_coord - (player_pos.x - (grid_sz.w - 1) / 2)) * tl_sz.w};
    auto w_area{get_ston<world>().get_current_world_area()};
    auto extra_rows{8};
    auto top_y_coord{c_int(player_pos.y - (grid_sz.h - 1) / 2) - extra_rows};
    auto player_tl{w_area->get_tile(player_pos)};
    auto player_elev{player_tl ? w_area->get_tile(player_pos)->get_elevation()
                               : 0};
    auto screen_rel_y_px{-extra_rows * tl_sz.h};
    for (auto y = -extra_rows; y < grid_sz.h + extra_rows; y++) {
      auto y_coord{c_int(player_pos.y - (grid_sz.h - 1) / 2 + y)};
      auto coord{point{hovered_x_coord, y_coord}};
      auto tl{w_area->get_tile(coord)};
      if (!tl) {
        screen_rel_y_px = 0.5f + (y - (grid_sz.h - 1) / 2) * tl_sz.h +
                          player_elev * tl_sz.h / 2;
        continue;
      }
      auto elev{tl->get_elevation()};
      screen_rel_y_px = 0.5f + (y - (grid_sz.h - 1) / 2) * tl_sz.h +
                        (player_elev - elev) * tl_sz.h / 2;
      auto coord_nw{point{coord.x, coord.y}};
      auto coord_ne{point{coord.x + 1, coord.y}};
      auto coord_sw{point{coord.x, coord.y + 1}};
      auto coord_se{point{coord.x + 1, coord.y + 1}};
      if (!w_area->is_valid_coordinate(coord_nw.x, coord_nw.y) ||
          !w_area->is_valid_coordinate(coord_ne.x, coord_ne.y) ||
          !w_area->is_valid_coordinate(coord_sw.x, coord_sw.y) ||
          !w_area->is_valid_coordinate(coord_se.x, coord_se.y)) {
        continue;
      }
      auto tl_nw{w_area->get_tile(coord_nw)};
      auto tl_ne{w_area->get_tile(coord_ne)};
      auto tl_sw{w_area->get_tile(coord_sw)};
      auto tl_se{w_area->get_tile(coord_se)};
      if (!tl_nw || !tl_ne || !tl_se || !tl_sw) {
        continue;
      }
      float local_tl_h;
      if (tl_nw->get_elevation() > tl_sw->get_elevation() &&
          tl_ne->get_elevation() > tl_se->get_elevation()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elevation() < tl_sw->get_elevation() &&
                 tl_ne->get_elevation() < tl_se->get_elevation()) {
        local_tl_h = tl_sz.h * 0.5f;
      } else if (tl_ne->get_elevation() > tl_nw->get_elevation() &&
                 tl_se->get_elevation() > tl_sw->get_elevation()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elevation() > tl_ne->get_elevation() &&
                 tl_sw->get_elevation() > tl_se->get_elevation()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elevation() > tl_ne->get_elevation() &&
                 tl_nw->get_elevation() > tl_se->get_elevation() &&
                 tl_nw->get_elevation() > tl_sw->get_elevation()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_ne->get_elevation() > tl_nw->get_elevation() &&
                 tl_ne->get_elevation() > tl_se->get_elevation() &&
                 tl_ne->get_elevation() > tl_sw->get_elevation()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_sw->get_elevation() > tl_nw->get_elevation() &&
                 tl_sw->get_elevation() > tl_se->get_elevation() &&
                 tl_sw->get_elevation() > tl_ne->get_elevation()) {
        local_tl_h = tl_sz.h * 1.0f;
      } else if (tl_se->get_elevation() > tl_nw->get_elevation() &&
                 tl_se->get_elevation() > tl_ne->get_elevation() &&
                 tl_se->get_elevation() > tl_sw->get_elevation()) {
        local_tl_h = tl_sz.h * 1.0f;
      } else if (tl_sw->get_elevation() < tl_nw->get_elevation() &&
                 tl_sw->get_elevation() < tl_ne->get_elevation() &&
                 tl_sw->get_elevation() < tl_se->get_elevation()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_se->get_elevation() < tl_nw->get_elevation() &&
                 tl_se->get_elevation() < tl_ne->get_elevation() &&
                 tl_se->get_elevation() < tl_sw->get_elevation()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elevation() < tl_ne->get_elevation() &&
                 tl_nw->get_elevation() < tl_sw->get_elevation() &&
                 tl_nw->get_elevation() < tl_se->get_elevation()) {
        local_tl_h = tl_sz.h * 1.0f;
      } else if (tl_ne->get_elevation() < tl_nw->get_elevation() &&
                 tl_ne->get_elevation() < tl_sw->get_elevation() &&
                 tl_ne->get_elevation() < tl_se->get_elevation()) {
        local_tl_h = tl_sz.h * 1.0f;
      } else if (tl_sw->get_elevation() == tl_ne->get_elevation() &&
                 tl_nw->get_elevation() < tl_sw->get_elevation() &&
                 tl_se->get_elevation() < tl_sw->get_elevation()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elevation() == tl_se->get_elevation() &&
                 tl_ne->get_elevation() < tl_nw->get_elevation() &&
                 tl_sw->get_elevation() < tl_nw->get_elevation()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else {
        local_tl_h = tl_sz.h;
      }
      auto rect{rect_f{screen_rel_x_px, screen_rel_y_px - local_tl_h / 2,
                       tl_sz.w, local_tl_h}};
      if (rect.contains(mouse_pos)) {
        m_hovered_coord = {hovered_x_coord, y_coord};
        return;
      }
    }
  }
}