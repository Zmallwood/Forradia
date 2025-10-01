/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_mouse_movement.hpp"
#include "core/input/mouse/mouse_input.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"
#include "theme_0/theme_0_mechanics/world_interaction/tile_hovering.hpp"

namespace forr {
  void UpdateMouseMovement() {
    if (GetSingleton<mouse_input>()
            .get_left_mouse_button_ref()
            .get_has_been_fired_pick_result()) {
      auto newDestination{
          GetSingleton<tile_hovering>().get_hovered_coordinate()};
      GetSingleton<player>().set_destination(newDestination);
    }
    auto playerPosition{GetSingleton<player>().get_position()};
    auto destination{GetSingleton<player>().get_destination()};
    if (destination == point{-1, -1}) {
      return;
    }
    auto now{GetTicks()};
    if (now >=
        GetSingleton<player>().get_ticks_last_move() +
            InvertMovementSpeed(GetSingleton<player>().get_movement_speed())) {
      auto dx{destination.x - playerPosition.x};
      auto dy{destination.y - playerPosition.y};
      if (dx < 0) {
        GetSingleton<player>().move_west();
      }
      if (dy < 0) {
        GetSingleton<player>().move_north();
      }
      if (dx > 0) {
        GetSingleton<player>().move_east();
      }
      if (dy > 0) {
        GetSingleton<player>().move_south();
      }
      if (destination == playerPosition) {
        GetSingleton<player>().set_destination({-1, -1});
      }
      GetSingleton<player>().set_ticks_last_move(now);
    }
  }
}