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
    if (get_singleton<mouse_input>()
            .get_left_mouse_button_ref()
            .get_has_been_fired_pick_result()) {
      auto new_dest{get_singleton<tile_hovering>().get_hovered_coordinate()};
      get_singleton<player>().set_destination(new_dest);
    }
    auto player_pos{get_singleton<player>().get_position()};
    auto dest{get_singleton<player>().get_destination()};
    if (dest == point{-1, -1}) {
      return;
    }
    auto now{get_ticks()};
    if (now >= get_singleton<player>().get_ticks_last_move() +
                   invert_movement_speed(
                       get_singleton<player>().get_movement_speed())) {
      auto dx{dest.x - player_pos.x};
      auto dy{dest.y - player_pos.y};
      if (dx < 0) {
        get_singleton<player>().move_west();
      }
      if (dy < 0) {
        get_singleton<player>().move_north();
      }
      if (dx > 0) {
        get_singleton<player>().move_east();
      }
      if (dy > 0) {
        get_singleton<player>().move_south();
      }
      if (dest == player_pos) {
        get_singleton<player>().set_destination({-1, -1});
      }
      get_singleton<player>().set_ticks_last_move(now);
    }
  }
}