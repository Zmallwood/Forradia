/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_mouse_movem.hpp"
#include "core/input.hpp"
#include "theme_0/func/core_game_objects/player.hpp"
#include "theme_0/func/world_interaction/tile_hovering.hpp"

namespace forr {
  void update_mouse_movem() {
    if (get_ston<mouse_input>()
            .get_left_btn_ref()
            .get_been_fired_pick_result()) {
      auto new_dest{get_ston<tile_hovering>().get_hovered_coord()};
      get_ston<player>().set_dest(new_dest);
    }
    auto player_pos{get_ston<player>().get_pos()};
    auto dest{get_ston<player>().get_dest()};
    if (dest == point{-1, -1}) {
      return;
    }
    auto now{get_ticks()};
    if (now >=
        get_ston<player>().get_ticks_last_move() +
            inv_movem_spd(get_ston<player>().get_movem_spd())) {
      auto dx{dest.x - player_pos.x};
      auto dy{dest.y - player_pos.y};
      if (dx < 0) {
        get_ston<player>().move_w();
      }
      if (dy < 0) {
        get_ston<player>().move_n();
      }
      if (dx > 0) {
        get_ston<player>().move_e();
      }
      if (dy > 0) {
        get_ston<player>().move_s();
      }
      if (dest == player_pos) {
        get_ston<player>().set_dest({-1, -1});
      }
      get_ston<player>().set_ticks_last_move(now);
    }
  }
}