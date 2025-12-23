/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateKeyboardMovement.hpp"
#include "Player/Player.hpp"

namespace Forradia::Theme0
{
    namespace
    {
        static std::set<SDL_Keycode> pressedKeys{};
    }

    auto UpdateKeyboardMovementStart(SDL_Keycode key) -> void
    {
        pressedKeys.insert(key);

        auto upPress{pressedKeys.contains(SDLK_UP) || pressedKeys.contains(SDLK_w)};
        auto rightPress{pressedKeys.contains(SDLK_RIGHT) || pressedKeys.contains(SDLK_d)};
        auto downPress{pressedKeys.contains(SDLK_DOWN) || pressedKeys.contains(SDLK_s)};
        auto leftPress{pressedKeys.contains(SDLK_LEFT) || pressedKeys.contains(SDLK_a)};

        if (upPress || rightPress || downPress || leftPress)
        {
            Player::Instance().SetDestination({-1, -1});
        }

        if (upPress && rightPress)
        {
            Player::Instance().StartMovingNorthEast();
        }
        else if (downPress && rightPress)
        {
            Player::Instance().StartMovingSouthEast();
        }
        else if (downPress && leftPress)
        {
            Player::Instance().StartMovingSouthWest();
        }
        else if (upPress && leftPress)
        {
            Player::Instance().StartMovingNorthWest();
        }
        else if (leftPress)
        {
            Player::Instance().StartMovingWest();
        }
        else if (upPress)
        {
            Player::Instance().StartMovingNorth();
        }
        else if (rightPress)
        {
            Player::Instance().StartMovingEast();
        }
        else if (downPress)
        {
            Player::Instance().StartMovingSouth();
        }
        else if (leftPress)
        {
            Player::Instance().StartMovingWest();
        }
    }

    auto UpdateKeyboardMovementStop() -> void
    {
        pressedKeys.clear();

        Player::Instance().StopMoving();
    }
}
