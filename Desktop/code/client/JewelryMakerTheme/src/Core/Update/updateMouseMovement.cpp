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

        if (destination == Point{-1, -1})
        {
            return;
        }

        auto now{getTicks()};

        if (now >= Player::instance().getTicksLastMovement() +
                       invertSpeed(Player::instance().getMovementSpeed()))
        {
            auto deltaX{destination.x - playerPosition.x};
            auto deltaY{destination.y - playerPosition.y};

            if (deltaX > 0 && deltaY < 0)
            {
                Player::instance().moveNorthEast();
            }
            else if (deltaX > 0 && deltaY > 0)
            {
                Player::instance().moveSouthEast();
            }
            else if (deltaX < 0 && deltaY > 0)
            {
                Player::instance().moveSouthWest();
            }
            else if (deltaX < 0 && deltaY < 0)
            {
                Player::instance().moveNorthWest();
            }
            else if (deltaX < 0)
            {
                Player::instance().moveWest();
            }
            else if (deltaY < 0)
            {
                Player::instance().moveNorth();
            }
            else if (deltaX > 0)
            {
                Player::instance().moveEast();
            }
            else if (deltaY > 0)
            {
                Player::instance().moveSouth();
            }

            if (destination == playerPosition)
            {
                Player::instance().setDestination({-1, -1});
                Player::instance().stopMoving();
            }

            Player::instance().setTicksLastMovement(now);
        }
    }
}
