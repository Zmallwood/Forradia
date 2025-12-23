/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateMouseMovement.hpp"
#include "NumbersUtilities.hpp"
#include "Player/Player.hpp"
#include "TimeUtilities.hpp"

namespace Forradia::Theme0
{
    auto UpdateMouseMovement() -> void
    {
        auto playerPosition{Player::Instance().GetPosition()};
        auto destination{Player::Instance().GetDestination()};

        if (destination == Point{-1, -1})
        {
            return;
        }

        auto now{GetTicks()};

        if (now >= Player::Instance().GetTicksLastMovement() +
                       InvertSpeed(Player::Instance().GetMovementSpeed()))
        {
            auto deltaX{destination.x - playerPosition.x};
            auto deltaY{destination.y - playerPosition.y};

            if (deltaX > 0 && deltaY < 0)
            {
                Player::Instance().MoveNorthEast();
            }
            else if (deltaX > 0 && deltaY > 0)
            {
                Player::Instance().MoveSouthEast();
            }
            else if (deltaX < 0 && deltaY > 0)
            {
                Player::Instance().MoveSouthWest();
            }
            else if (deltaX < 0 && deltaY < 0)
            {
                Player::Instance().MoveNorthWest();
            }
            else if (deltaX < 0)
            {
                Player::Instance().MoveWest();
            }
            else if (deltaY < 0)
            {
                Player::Instance().MoveNorth();
            }
            else if (deltaX > 0)
            {
                Player::Instance().MoveEast();
            }
            else if (deltaY > 0)
            {
                Player::Instance().MoveSouth();
            }

            if (destination == playerPosition)
            {
                Player::Instance().SetDestination({-1, -1});
            }

            Player::Instance().SetTicksLastMovement(now);
        }
    }
}
