/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "updateKeyboardMovement.hpp"
#include <set>
#include "Player/Player.hpp"

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

        auto isClimbingTree{Player::instance().getIsClimbingTree()};

        If(!isClimbingTree)
        {
            If(upPress || rightPress || downPress || leftPress)
            {
                Player::instance().setDestination({-1, -1});
            }

            If(upPress && rightPress)
            {
                Player::instance().startMovingNorthEast();
            }
            ElseIf(downPress && rightPress)
            {
                Player::instance().startMovingSouthEast();
            }
            ElseIf(downPress && leftPress)
            {
                Player::instance().startMovingSouthWest();
            }
            ElseIf(upPress && leftPress)
            {
                Player::instance().startMovingNorthWest();
            }
            ElseIf(leftPress)
            {
                Player::instance().startMovingWest();
            }
            ElseIf(upPress)
            {
                Player::instance().startMovingNorth();
            }
            ElseIf(rightPress)
            {
                Player::instance().startMovingEast();
            }
            ElseIf(downPress)
            {
                Player::instance().startMovingSouth();
            }
            ElseIf(leftPress)
            {
                Player::instance().startMovingWest();
            }
        }
        Else
        {
            If(upPress)
            {
                Player::instance().addToClimbingHeight(1.0F);
            }
            ElseIf(downPress)
            {
                Player::instance().addToClimbingHeight(-1.0F);
            }
        }
    }

    auto updateKeyboardMovementStop() -> void
    {
        pressedKeys.clear();

        Player::instance().stopMoving();
    }
}
