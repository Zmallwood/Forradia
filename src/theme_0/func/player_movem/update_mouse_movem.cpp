/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_mouse_movem.hpp"
#include "input.hpp"
#include "theme_0/func/core_objs/player.hpp"
#include "theme_0/func/world_interact/tile_hovering.hpp"

namespace forr {
  void update_mouse_movem() {
    if (_<mouse_input>().get_left_btn_ref().get_been_fired_pick_result()) {
      auto new_dest{_<tile_hovering>().get_hovered_coord()};
      _<player>().set_dest(new_dest);
    }
    auto player_pos{_<player>().get_pos()};
    auto dest{_<player>().get_dest()};
    if (dest == point{-1, -1}) {
      return;
    }
    auto now{get_ticks()};
    if (now >= _<player>().get_ticks_last_move() +
                   inv_movem_spd(_<player>().get_movem_spd())) {
      auto dx{dest.x - player_pos.x};
      auto dy{dest.y - player_pos.y};
      if (dx < 0) {
        _<player>().move_w();
      }
      if (dy < 0) {
        _<player>().move_n();
      }
      if (dx > 0) {
        _<player>().move_e();
      }
      if (dy > 0) {
        _<player>().move_s();
      }
      if (dest == player_pos) {
        _<player>().set_dest({-1, -1});
      }
      _<player>().set_ticks_last_move(now);
    }
  }
}