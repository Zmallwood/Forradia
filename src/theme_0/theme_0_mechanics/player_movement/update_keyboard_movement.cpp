/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_keyboard_movement.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"

namespace forr {
  void UpdateKeyboardMovement() {
    auto upPressed{GetSingleton<keyboard_input>().key_is_pressed(SDLK_UP)};
    auto rightPressed{
        GetSingleton<keyboard_input>().key_is_pressed(SDLK_RIGHT)};
    auto downPressed{GetSingleton<keyboard_input>().key_is_pressed(SDLK_DOWN)};
    auto leftPressed{GetSingleton<keyboard_input>().key_is_pressed(SDLK_LEFT)};
    if (upPressed || rightPressed || downPressed || leftPressed) {
      GetSingleton<player>().set_destination({-1, -1});
    }
    auto now{GetTicks()};
    if (now >= GetSingleton<player>().get_ticks_last_move() +
                   InvertMovementSpeed(
                       GetSingleton<player>().get_movement_speed()) &&
        (upPressed || rightPressed || downPressed || leftPressed)) {
      if (upPressed) {
        GetSingleton<player>().move_north();
      }
      if (rightPressed) {
        GetSingleton<player>().move_east();
      }
      if (downPressed) {
        GetSingleton<player>().move_south();
      }
      if (leftPressed) {
        GetSingleton<player>().move_west();
      }
      GetSingleton<player>().set_ticks_last_move(now);
    }
  }
}