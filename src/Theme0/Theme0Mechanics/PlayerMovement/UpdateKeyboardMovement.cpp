/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "UpdateKeyboardMovement.hpp"
#include "Core/Input/Keyboard/KeyboardInput.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"

namespace Forradia {
  void UpdateKeyboardMovement() {
    auto upPressed{_<KeyboardInput>().KeyIsPressed(SDLK_UP)};
    auto rightPressed{_<KeyboardInput>().KeyIsPressed(SDLK_RIGHT)};
    auto downPressed{_<KeyboardInput>().KeyIsPressed(SDLK_DOWN)};
    auto leftPressed{_<KeyboardInput>().KeyIsPressed(SDLK_LEFT)};

    if (upPressed || rightPressed || downPressed || leftPressed) {
      _<Player>().SetDestination({-1, -1});
    }

    auto now{GetTicks()};

    if (now >= _<Player>().GetTicksLastMove() +
                   InvertMovementSpeed(_<Player>().GetMovementSpeed()) &&
        (upPressed || rightPressed || downPressed || leftPressed)) {
      if (upPressed) {
        _<Player>().MoveNorth();
      }

      if (rightPressed) {
        _<Player>().MoveEast();
      }

      if (downPressed) {
        _<Player>().MoveSouth();
      }

      if (leftPressed) {
        _<Player>().MoveWest();
      }

      _<Player>().SetTicksLastMove(now);
    }
  }
}