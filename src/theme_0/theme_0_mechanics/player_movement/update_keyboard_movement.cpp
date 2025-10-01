/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "update_keyboard_movement.hpp"
#include "core/input/keyboard/keyboard_input.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"

namespace forr {
  void UpdateKeyboardMovement() {
    auto upPressed{GetSingleton<keyboard_input>().KeyIsPressed(SDLK_UP)};
    auto rightPressed{GetSingleton<keyboard_input>().KeyIsPressed(SDLK_RIGHT)};
    auto downPressed{GetSingleton<keyboard_input>().KeyIsPressed(SDLK_DOWN)};
    auto leftPressed{GetSingleton<keyboard_input>().KeyIsPressed(SDLK_LEFT)};
    if (upPressed || rightPressed || downPressed || leftPressed) {
      GetSingleton<player>().SetDestination({-1, -1});
    }
    auto now{GetTicks()};
    if (now >= GetSingleton<player>().GetTicksLastMove() +
                   InvertMovementSpeed(
                       GetSingleton<player>().GetMovementSpeed()) &&
        (upPressed || rightPressed || downPressed || leftPressed)) {
      if (upPressed) {
        GetSingleton<player>().MoveNorth();
      }
      if (rightPressed) {
        GetSingleton<player>().MoveEast();
      }
      if (downPressed) {
        GetSingleton<player>().MoveSouth();
      }
      if (leftPressed) {
        GetSingleton<player>().MoveWest();
      }
      GetSingleton<player>().SetTicksLastMove(now);
    }
  }
}