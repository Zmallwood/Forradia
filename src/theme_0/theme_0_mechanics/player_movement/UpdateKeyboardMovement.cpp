/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "UpdateKeyboardMovement.hpp"
#include "core/input/keyboard/KeyboardInput.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/Player.hpp"

namespace Forradia {
  void UpdateKeyboardMovement() {
    auto upPressed{GetSingleton<KeyboardInput>().KeyIsPressed(SDLK_UP)};
    auto rightPressed{GetSingleton<KeyboardInput>().KeyIsPressed(SDLK_RIGHT)};
    auto downPressed{GetSingleton<KeyboardInput>().KeyIsPressed(SDLK_DOWN)};
    auto leftPressed{GetSingleton<KeyboardInput>().KeyIsPressed(SDLK_LEFT)};

    if (upPressed || rightPressed || downPressed || leftPressed) {
      GetSingleton<Player>().SetDestination({-1, -1});
    }

    auto now{GetTicks()};

    if (now >= GetSingleton<Player>().GetTicksLastMove() +
                   InvertMovementSpeed(
                       GetSingleton<Player>().GetMovementSpeed()) &&
        (upPressed || rightPressed || downPressed || leftPressed)) {
      if (upPressed) {
        GetSingleton<Player>().MoveNorth();
      }

      if (rightPressed) {
        GetSingleton<Player>().MoveEast();
      }

      if (downPressed) {
        GetSingleton<Player>().MoveSouth();
      }

      if (leftPressed) {
        GetSingleton<Player>().MoveWest();
      }

      GetSingleton<Player>().SetTicksLastMove(now);
    }
  }
}