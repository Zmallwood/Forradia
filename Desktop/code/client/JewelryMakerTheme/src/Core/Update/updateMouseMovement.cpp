/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "updateMouseMovement.hpp"
#include "Player/Player.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto updateMouseMovement() -> void
    {
        auto playerPosition{Player::instance().getPosition()};
        auto destination{Player::instance().getDestination()};

        If(destination == Point{-1, -1})
        {
            return;
        }

        auto now{getTicks()};

        If(now >= Player::instance().getTicksLastMovement() +
                      invertSpeed(Player::instance().getMovementSpeed()))
        {
            auto deltaX{destination.x - playerPosition.x};
            auto deltaY{destination.y - playerPosition.y};

            If(deltaX > 0 && deltaY < 0)
            {
                Player::instance().moveNorthEast();
            }
            ElseIf(deltaX > 0 && deltaY > 0)
            {
                Player::instance().moveSouthEast();
            }
            ElseIf(deltaX < 0 && deltaY > 0)
            {
                Player::instance().moveSouthWest();
            }
            ElseIf(deltaX < 0 && deltaY < 0)
            {
                Player::instance().moveNorthWest();
            }
            ElseIf(deltaX < 0)
            {
                Player::instance().moveWest();
            }
            ElseIf(deltaY < 0)
            {
                Player::instance().moveNorth();
            }
            ElseIf(deltaX > 0)
            {
                Player::instance().moveEast();
            }
            ElseIf(deltaY > 0)
            {
                Player::instance().moveSouth();
            }

            If(destination == playerPosition)
            {
                Player::instance().setDestination({-1, -1});
                Player::instance().stopMoving();
            }

            Player::instance().setTicksLastMovement(now);
        }
    }
}
