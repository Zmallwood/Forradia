/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_keyboard_movement.hpp"
#include "core/input.hpp"
#include "theme_0/mechanics/core_game_objects/player.hpp"

namespace forr {
  void update_keyboard_movement() {
    auto up_press{get_singleton<keyboard_input>().key_is_pressed(SDLK_UP)};
    auto right_press{
        get_singleton<keyboard_input>().key_is_pressed(SDLK_RIGHT)};
    auto down_press{get_singleton<keyboard_input>().key_is_pressed(SDLK_DOWN)};
    auto left_press{get_singleton<keyboard_input>().key_is_pressed(SDLK_LEFT)};
    if (up_press || right_press || down_press || left_press) {
      get_singleton<player>().set_destination({-1, -1});
    }
    auto now{get_ticks()};
    if (now >= get_singleton<player>().get_ticks_last_move() +
                   invert_movement_speed(
                       get_singleton<player>().get_movement_speed()) &&
        (up_press || right_press || down_press || left_press)) {
      if (up_press) {
        get_singleton<player>().move_north();
      }
      if (right_press) {
        get_singleton<player>().move_east();
      }
      if (down_press) {
        get_singleton<player>().move_south();
      }
      if (left_press) {
        get_singleton<player>().move_west();
      }
      get_singleton<player>().set_ticks_last_move(now);
    }
  }
}