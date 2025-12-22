/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateMouseMovement.hpp"
#include "NumbersUtilities.hpp"
#include "Player/Player.hpp"
#include "TileHovering.hpp"

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
            auto dX{destination.x - playerPosition.x};
            auto dY{destination.y - playerPosition.y};

            if (dX < 0)
            {
                Player::Instance().MoveWest();
            }

            if (dY < 0)
            {
                Player::Instance().MoveNorth();
            }

            if (dX > 0)
            {
                Player::Instance().MoveEast();
            }

            if (dY > 0)
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
