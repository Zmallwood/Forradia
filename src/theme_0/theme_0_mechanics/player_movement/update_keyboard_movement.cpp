/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_keyboard_movement.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"

namespace forr {
  void update_keyboard_movement() {
    auto upPressed{get_singleton<keyboard_input>().key_is_pressed(SDLK_UP)};
    auto rightPressed{
        get_singleton<keyboard_input>().key_is_pressed(SDLK_RIGHT)};
    auto downPressed{get_singleton<keyboard_input>().key_is_pressed(SDLK_DOWN)};
    auto leftPressed{get_singleton<keyboard_input>().key_is_pressed(SDLK_LEFT)};
    if (upPressed || rightPressed || downPressed || leftPressed) {
      get_singleton<player>().set_destination({-1, -1});
    }
    auto now{get_ticks()};
    if (now >= get_singleton<player>().get_ticks_last_move() +
                   invert_movement_speed(
                       get_singleton<player>().get_movement_speed()) &&
        (upPressed || rightPressed || downPressed || leftPressed)) {
      if (upPressed) {
        get_singleton<player>().move_north();
      }
      if (rightPressed) {
        get_singleton<player>().move_east();
      }
      if (downPressed) {
        get_singleton<player>().move_south();
      }
      if (leftPressed) {
        get_singleton<player>().move_west();
      }
      get_singleton<player>().set_ticks_last_move(now);
    }
  }
}