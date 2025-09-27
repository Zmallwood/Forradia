/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "UpdateMouseMovement.hpp"
#include "Core/Input/Mouse/MouseInput.hpp"
#include "Theme0/Theme0Mechanics/WorldInteraction/TileHovering.hpp"
#include "Theme0/Theme0Mechanics/CoreGameObjects/Player.hpp"

namespace Forradia
{
    void UpdateMouseMovement()
    {
        if (_<MouseInput>().GetLeftMouseButtonRef().IsPressedPickResult())
        {
            auto newDestination{_<TileHovering>().GetHoveredCoordinate()};

            _<Player>().SetDestination(newDestination);
        }

        auto playerPosition{_<Player>().GetPosition()};

        auto destination{_<Player>().GetDestination()};

        if (destination == Point{-1, -1})
        {
            return;
        }

        auto now{GetTicks()};

        if (now >= _<Player>().GetTicksLastMove() + InvertMovementSpeed(_<Player>().GetMovementSpeed()))
        {

            auto dx{destination.x - playerPosition.x};
            auto dy{destination.y - playerPosition.y};

            if (dx < 0)
            {
                _<Player>().MoveWest();
            }

            if (dy < 0)
            {
                _<Player>().MoveNorth();
            }

            if (dx > 0)
            {
                _<Player>().MoveEast();
            }

            if (dy > 0)
            {
                _<Player>().MoveSouth();
            }

            if (destination == playerPosition)
            {
                _<Player>().SetDestination({-1, -1});
            }

            _<Player>().SetTicksLastMove(now);
        }
    }
}