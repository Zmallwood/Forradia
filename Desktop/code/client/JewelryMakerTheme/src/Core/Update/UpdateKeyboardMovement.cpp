/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateKeyboardMovement.hpp"
#include <set>
#include "Essentials/Player/Player.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    namespace
    {
        std::set<SDL_Keycode> pressedKeys{};
    }

    auto updateKeyboardMovementStart(SDL_Keycode key) -> void
    {
        pressedKeys.insert(key);

        auto upPress{pressedKeys.contains(SDLK_UP) || pressedKeys.contains(SDLK_w)};
        auto rightPress{pressedKeys.contains(SDLK_RIGHT) || pressedKeys.contains(SDLK_d)};
        auto downPress{pressedKeys.contains(SDLK_DOWN) || pressedKeys.contains(SDLK_s)};
        auto leftPress{pressedKeys.contains(SDLK_LEFT) || pressedKeys.contains(SDLK_a)};

        if (upPress || rightPress || downPress || leftPress)
        {
            Player::instance().setDestination({-1, -1});
        }

        if (upPress && rightPress)
        {
            Player::instance().startMovingNorthEast();
        }
        else if (downPress && rightPress)
        {
            Player::instance().startMovingSouthEast();
        }
        else if (downPress && leftPress)
        {
            Player::instance().startMovingSouthWest();
        }
        else if (upPress && leftPress)
        {
            Player::instance().startMovingNorthWest();
        }
        else if (leftPress)
        {
            Player::instance().startMovingWest();
        }
        else if (upPress)
        {
            Player::instance().startMovingNorth();
        }
        else if (rightPress)
        {
            Player::instance().startMovingEast();
        }
        else if (downPress)
        {
            Player::instance().startMovingSouth();
        }
        else if (leftPress)
        {
            Player::instance().startMovingWest();
        }
    }

    auto updateKeyboardMovementStop() -> void
    {
        pressedKeys.clear();

        Player::instance().stopMoving();
    }
}
