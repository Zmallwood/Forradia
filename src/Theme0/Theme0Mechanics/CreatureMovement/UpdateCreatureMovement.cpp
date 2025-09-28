/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "UpdateCreatureMovement.hpp"
#include "Sub/GenerateNewCreatureDestination.hpp"
#include "Sub/CalculateNewCreaturePosition.hpp"
#include "Sub/MoveCreatureToNewLocation.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Creature.hpp"

namespace Forradia
{
    void UpdateCreatureMovement()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto &creaturesMirrorRef{worldArea->GetCreaturesMirrorRef()};

        auto now{GetTicks()};

        for (auto it = creaturesMirrorRef.begin(); it != creaturesMirrorRef.end();)
        {
            auto creature{it->first};
            auto position{it->second};

            if (now < creature->GetTicksLastMove() + InvertMovementSpeed(creature->GetMovementSpeed()))
            {
                ++it;
                continue;
            }

            GenerateNewCreatureDestination(creature);

            auto newPosition {CalculateNewCreaturePosition(creature)};

            if (newPosition == creature->GetDestination())
            {
                creature->SetDestination({-1, -1});
            }

            auto tile{worldArea->GetTile(newPosition.x, newPosition.y)};

            if (tile && !tile->GetCreature() && tile->GetGround() != Hash("GroundWater"))
            {
                MoveCreatureToNewLocation(creature, {newPosition.x, newPosition.y});
            }
            else
            {
                creature->SetDestination({-1, -1});
            }

            ++it;
        }
    }
}