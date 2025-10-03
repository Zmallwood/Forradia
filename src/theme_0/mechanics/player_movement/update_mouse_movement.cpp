/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_mouse_movement.hpp"
#include "core/input.hpp"
#include "theme_0/mechanics/core_game_objects/player.hpp"
#include "theme_0/mechanics/world_interaction/tile_hovering.hpp"

namespace forr {
  void update_mouse_movement() {
    if (get_ston<mouse_input>()
            .get_left_btn_ref()
            .get_been_fired_pick_result()) {
      auto new_dest{get_ston<tile_hovering>().get_hovered_coordinate()};
      get_ston<player>().set_destination(new_dest);
    }
    auto player_pos{get_ston<player>().get_position()};
    auto dest{get_ston<player>().get_destination()};
    if (dest == point{-1, -1}) {
      return;
    }
    auto now{get_ticks()};
    if (now >=
        get_ston<player>().get_ticks_last_move() +
            inv_movem_spd(get_ston<player>().get_movement_speed())) {
      auto dx{dest.x - player_pos.x};
      auto dy{dest.y - player_pos.y};
      if (dx < 0) {
        get_ston<player>().move_west();
      }
      if (dy < 0) {
        get_ston<player>().move_north();
      }
      if (dx > 0) {
        get_ston<player>().move_east();
      }
      if (dy > 0) {
        get_ston<player>().move_south();
      }
      if (dest == player_pos) {
        get_ston<player>().set_destination({-1, -1});
      }
      get_ston<player>().set_ticks_last_move(now);
    }
  }
}