/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile_hovering.hpp"
#include "theme_0/func/core_objs/player.hpp"
#include "theme_0/func/math/tile_grid_math.hpp"
#include "theme_0/func/world_struct/tile.hpp"
#include "theme_0/func/world_struct/world.hpp"
#include "theme_0/func/world_struct/world_area.hpp"

namespace forr {
  void tile_hovering::update() {
    auto player_pos{get_ston<player>().get_pos()};
    auto mouse_pos{get_norm_mouse_pos()};
    auto tl_sz{calc_tl_sz()};
    auto screen_rel_x{c_int(mouse_pos.x / tl_sz.w)};
    auto grid_sz{calc_grid_sz()};
    auto hovered_x_coord{player_pos.x - (grid_sz.w - 1) / 2 + screen_rel_x};
    auto screen_rel_x_px{
        (hovered_x_coord - (player_pos.x - (grid_sz.w - 1) / 2)) * tl_sz.w};
    auto w_area{get_ston<world>().get_curr_w_area()};
    auto extra_rows{8};
    auto top_y_coord{c_int(player_pos.y - (grid_sz.h - 1) / 2) - extra_rows};
    auto player_tl{w_area->get_tl(player_pos)};
    auto player_elev{player_tl ? w_area->get_tl(player_pos)->get_elev()
                               : 0};
    auto screen_rel_y_px{-extra_rows * tl_sz.h};
    for (auto y = -extra_rows; y < grid_sz.h + extra_rows; y++) {
      auto y_coord{c_int(player_pos.y - (grid_sz.h - 1) / 2 + y)};
      auto coord{point{hovered_x_coord, y_coord}};
      auto tl{w_area->get_tl(coord)};
      if (!tl) {
        screen_rel_y_px = 0.5f + (y - (grid_sz.h - 1) / 2) * tl_sz.h +
                          player_elev * tl_sz.h / 2;
        continue;
      }
      auto elev{tl->get_elev()};
      screen_rel_y_px = 0.5f + (y - (grid_sz.h - 1) / 2) * tl_sz.h +
                        (player_elev - elev) * tl_sz.h / 2;
      auto coord_nw{point{coord.x, coord.y}};
      auto coord_ne{point{coord.x + 1, coord.y}};
      auto coord_sw{point{coord.x, coord.y + 1}};
      auto coord_se{point{coord.x + 1, coord.y + 1}};
      if (!w_area->is_valid_coord(coord_nw.x, coord_nw.y) ||
          !w_area->is_valid_coord(coord_ne.x, coord_ne.y) ||
          !w_area->is_valid_coord(coord_sw.x, coord_sw.y) ||
          !w_area->is_valid_coord(coord_se.x, coord_se.y)) {
        continue;
      }
      auto tl_nw{w_area->get_tl(coord_nw)};
      auto tl_ne{w_area->get_tl(coord_ne)};
      auto tl_sw{w_area->get_tl(coord_sw)};
      auto tl_se{w_area->get_tl(coord_se)};
      if (!tl_nw || !tl_ne || !tl_se || !tl_sw) {
        continue;
      }
      float local_tl_h;
      if (tl_nw->get_elev() > tl_sw->get_elev() &&
          tl_ne->get_elev() > tl_se->get_elev()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elev() < tl_sw->get_elev() &&
                 tl_ne->get_elev() < tl_se->get_elev()) {
        local_tl_h = tl_sz.h * 0.5f;
      } else if (tl_ne->get_elev() > tl_nw->get_elev() &&
                 tl_se->get_elev() > tl_sw->get_elev()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elev() > tl_ne->get_elev() &&
                 tl_sw->get_elev() > tl_se->get_elev()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elev() > tl_ne->get_elev() &&
                 tl_nw->get_elev() > tl_se->get_elev() &&
                 tl_nw->get_elev() > tl_sw->get_elev()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_ne->get_elev() > tl_nw->get_elev() &&
                 tl_ne->get_elev() > tl_se->get_elev() &&
                 tl_ne->get_elev() > tl_sw->get_elev()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_sw->get_elev() > tl_nw->get_elev() &&
                 tl_sw->get_elev() > tl_se->get_elev() &&
                 tl_sw->get_elev() > tl_ne->get_elev()) {
        local_tl_h = tl_sz.h * 1.0f;
      } else if (tl_se->get_elev() > tl_nw->get_elev() &&
                 tl_se->get_elev() > tl_ne->get_elev() &&
                 tl_se->get_elev() > tl_sw->get_elev()) {
        local_tl_h = tl_sz.h * 1.0f;
      } else if (tl_sw->get_elev() < tl_nw->get_elev() &&
                 tl_sw->get_elev() < tl_ne->get_elev() &&
                 tl_sw->get_elev() < tl_se->get_elev()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_se->get_elev() < tl_nw->get_elev() &&
                 tl_se->get_elev() < tl_ne->get_elev() &&
                 tl_se->get_elev() < tl_sw->get_elev()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elev() < tl_ne->get_elev() &&
                 tl_nw->get_elev() < tl_sw->get_elev() &&
                 tl_nw->get_elev() < tl_se->get_elev()) {
        local_tl_h = tl_sz.h * 1.0f;
      } else if (tl_ne->get_elev() < tl_nw->get_elev() &&
                 tl_ne->get_elev() < tl_sw->get_elev() &&
                 tl_ne->get_elev() < tl_se->get_elev()) {
        local_tl_h = tl_sz.h * 1.0f;
      } else if (tl_sw->get_elev() == tl_ne->get_elev() &&
                 tl_nw->get_elev() < tl_sw->get_elev() &&
                 tl_se->get_elev() < tl_sw->get_elev()) {
        local_tl_h = tl_sz.h * 1.5f;
      } else if (tl_nw->get_elev() == tl_se->get_elev() &&
                 tl_ne->get_elev() < tl_nw->get_elev() &&
                 tl_sw->get_elev() < tl_nw->get_elev()) {
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