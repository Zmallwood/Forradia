/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateKeyboardMovement.hpp"
#include "NumbersUtilities.hpp"
#include "Player/Player.hpp"

namespace Forradia::Theme0
{
    auto UpdateKeyboardMovementStart(SDL_Keycode key) -> void
    {
        auto upPress{key == SDLK_UP};
        auto rightPress{key == SDLK_RIGHT};
        auto downPress{key == SDLK_DOWN};
        auto leftPress{key == SDLK_LEFT};
        auto wPress{key == SDLK_w};
        auto aPress{key == SDLK_a};
        auto sPress{key == SDLK_s};
        auto dPress{key == SDLK_d};

        if (upPress || rightPress || downPress || leftPress || wPress || aPress || sPress || dPress)
        {
            Player::Instance().SetDestination({-1, -1});
        }

        auto now{GetTicks()};

        if (upPress || wPress)
            Player::Instance().StartMovingNorth();
        if (rightPress || dPress)
            Player::Instance().StartMovingEast();
        if (downPress || sPress)
            Player::Instance().StartMovingSouth();
        if (leftPress || aPress)
            Player::Instance().StartMovingWest();
    }

    auto UpdateKeyboardMovementStop() -> void
    {
        Player::Instance().StopMoving();
    }
}
