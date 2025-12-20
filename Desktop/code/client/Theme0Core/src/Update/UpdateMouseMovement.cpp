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
        auto playerPosition{_<Player>().GetPosition()};
        auto destination{_<Player>().GetDestination()};

        if (destination == Point{-1, -1})
            return;

        auto now{GetTicks()};

        if (now >=
            _<Player>().GetTicksLastMovement() + InvertSpeed(_<Player>().GetMovementSpeed())) {
            auto dX{destination.x - playerPosition.x};
            auto dY{destination.y - playerPosition.y};

            if (dX < 0)
                _<Player>().MoveWest();
            if (dY < 0)
                _<Player>().MoveNorth();
            if (dX > 0)
                _<Player>().MoveEast();
            if (dY > 0)
                _<Player>().MoveSouth();
            if (destination == playerPosition)
                _<Player>().SetDestination({-1, -1});

            _<Player>().SetTicksLastMovement(now);
        }
    }
}
