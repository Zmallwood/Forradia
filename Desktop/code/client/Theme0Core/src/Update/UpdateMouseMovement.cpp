/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateMouseMovement.hpp"
#include "NumbersUtilities.hpp"
#include "Player/Player.hpp"
#include "TileHovering.hpp"

namespace Forradia::Theme0 {
    auto UpdateMouseMovement() -> void {
        auto playerPosition{Singleton<Player>().GetPosition()};
        auto destination{Singleton<Player>().GetDestination()};

        if (destination == Point{-1, -1})
            return;

        auto now{GetTicks()};

        if (now >= Singleton<Player>().GetTicksLastMovement() +
                       InvertSpeed(Singleton<Player>().GetMovementSpeed())) {
            auto dX{destination.x - playerPosition.x};
            auto dY{destination.y - playerPosition.y};

            if (dX < 0)
                Singleton<Player>().MoveWest();
            if (dY < 0)
                Singleton<Player>().MoveNorth();
            if (dX > 0)
                Singleton<Player>().MoveEast();
            if (dY > 0)
                Singleton<Player>().MoveSouth();
            if (destination == playerPosition)
                Singleton<Player>().SetDestination({-1, -1});

            Singleton<Player>().SetTicksLastMovement(now);
        }
    }
}
