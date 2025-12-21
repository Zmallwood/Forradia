/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateKeyboardMovement.hpp"
#include "NumbersUtilities.hpp"
#include "Player/Player.hpp"

namespace Forradia::Theme0 {
    auto UpdateKeyboardMovementStart(SDL_Keycode key) -> void {
        auto upPress{key == SDLK_UP};
        auto rightPress{key == SDLK_RIGHT};
        auto downPress{key == SDLK_DOWN};
        auto leftPress{key == SDLK_LEFT};
        auto wPress{key == SDLK_w};
        auto aPress{key == SDLK_a};
        auto sPress{key == SDLK_s};
        auto dPress{key == SDLK_d};

        if (upPress || rightPress || downPress || leftPress || wPress || aPress || sPress ||
            dPress) {
            Singleton<Theme0::Player>().SetDestination({-1, -1});
        }

        auto now{GetTicks()};

        if (upPress || wPress)
            Singleton<Theme0::Player>().StartMovingNorth();
        if (rightPress || dPress)
            Singleton<Theme0::Player>().StartMovingEast();
        if (downPress || sPress)
            Singleton<Theme0::Player>().StartMovingSouth();
        if (leftPress || aPress)
            Singleton<Theme0::Player>().StartMovingWest();
    }

    auto UpdateKeyboardMovementStop() -> void {
        Singleton<Theme0::Player>().StopMoving();
    }
}
