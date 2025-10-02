/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_keyboard_movement.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "theme_0/mechanics/core_game_objects/player.hpp"

namespace forr {
  void update_keyboard_movement() {
    auto up_pressed{get_singleton<keyboard_input>().key_is_pressed(SDLK_UP)};
    auto right_pressed{
        get_singleton<keyboard_input>().key_is_pressed(SDLK_RIGHT)};
    auto down_pressed{
        get_singleton<keyboard_input>().key_is_pressed(SDLK_DOWN)};
    auto left_pressed{
        get_singleton<keyboard_input>().key_is_pressed(SDLK_LEFT)};
    if (up_pressed || right_pressed || down_pressed || left_pressed) {
      get_singleton<player>().set_destination({-1, -1});
    }
    auto now{get_ticks()};
    if (now >= get_singleton<player>().get_ticks_last_move() +
                   invert_movement_speed(
                       get_singleton<player>().get_movement_speed()) &&
        (up_pressed || right_pressed || down_pressed || left_pressed)) {
      if (up_pressed) {
        get_singleton<player>().move_north();
      }
      if (right_pressed) {
        get_singleton<player>().move_east();
      }
      if (down_pressed) {
        get_singleton<player>().move_south();
      }
      if (left_pressed) {
        get_singleton<player>().move_west();
      }
      get_singleton<player>().set_ticks_last_move(now);
    }
  }
}