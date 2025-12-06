//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "UpdateMouseMovement.hpp"
#include "BattleSystem.hpp"
#include "Mouse/MouseInput.hpp"
#include "NumbersUtilities.hpp"
#include "Player/PlayerCharacter.hpp"
#include "TileHovering.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void UpdateMouseMovement()
    {
        if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFiredPickResult())
        {
            auto newDestination{_<TileHovering>().GetHoveredCoordinate()};

            _<Theme0::GameplayCore::PlayerCharacter>().SetDestination(newDestination);

            _<GameplayCore::BattleSystem>().SetTargetedRobot(nullptr);
        }

        auto playerPosition{_<PlayerCharacter>().GetPosition()};

        auto destination{_<PlayerCharacter>().GetDestination()};

        if (destination == Point{-1, -1})
        {
            return;
        }

        auto now{GetTicks()};

        if (now >= _<PlayerCharacter>().GetTicksLastMovement() +
                       InvertSpeed(_<PlayerCharacter>().GetMovementSpeed()))
        {
            auto dX{destination.x - playerPosition.x};

            auto dY{destination.y - playerPosition.y};

            if (dX < 0)
            {
                _<PlayerCharacter>().MoveWest();
            }

            if (dY < 0)
            {
                _<PlayerCharacter>().MoveNorth();
            }

            if (dX > 0)
            {
                _<PlayerCharacter>().MoveEast();
            }

            if (dY > 0)
            {
                _<PlayerCharacter>().MoveSouth();
            }

            if (destination == playerPosition)
            {
                _<PlayerCharacter>().SetDestination({-1, -1});
            }

            _<PlayerCharacter>().SetTicksLastMovement(now);
        }
    }
}