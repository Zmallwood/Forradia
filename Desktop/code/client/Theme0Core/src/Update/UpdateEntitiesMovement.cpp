/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateEntitiesMovement.hpp"
#include "Entity.hpp"
#include "Hash.hpp"
#include "NumbersUtilities.hpp"
#include "RandomizationUtilities.hpp"
#include "Tile.hpp"
#include "TimeUtilities.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    auto UpdateEntitiesMovement() -> void
    {
        auto worldArea{World::Instance().GetCurrentWorldArea()};
        auto &entities{worldArea->GetEntitiesMirrorRef()};

        auto now{GetTicks()};

        for (auto it = entities.begin(); it != entities.end();)
        {
            auto entity{it->first};
            auto position{it->second};

            if (now < entity->GetTicksLastMovement() + InvertSpeed(entity->GetMovementSpeed()))
            {
                ++it;

                continue;
            }

            auto destination{entity->GetDestination()};

            if (destination.x == -1 && destination.y == -1)
            {
                // NOLINTNEXTLINE(readability-magic-numbers)
                auto newDestinationX{position.x + GetRandomInt(11) - 5};

                // NOLINTNEXTLINE(readability-magic-numbers)
                auto newDestinationY{position.y + GetRandomInt(11) - 5};

                entity->SetDestination({newDestinationX, newDestinationY});
            }

            auto worldArea{World::Instance().GetCurrentWorldArea()};
            auto &entities{worldArea->GetEntitiesMirrorRef()};

            auto deltaX{entity->GetDestination().x - position.x};
            auto deltaY{entity->GetDestination().y - position.y};

            auto normalizedDX{Normalize(deltaX)};
            auto normalizedDY{Normalize(deltaY)};

            auto newX{position.x + normalizedDX};
            auto newY{position.y + normalizedDY};

            Point newPosition{newX, newY};

            if (newPosition == entity->GetDestination())
            {
                entity->SetDestination({-1, -1});
            }

            auto tile{worldArea->GetTile(newPosition.x, newPosition.y)};

            if (tile && !tile->GetEntity() && tile->GetGround() != Hash("GroundWater"))
            {
                auto oldPosition{entities.at(entity)};

                entity->SetTicksLastMovement(now);

                auto oldTile{worldArea->GetTile(oldPosition.x, oldPosition.y)};
                auto newTile{worldArea->GetTile(newPosition.x, newPosition.y)};

                oldTile->SetEntity(nullptr);
                newTile->SetEntity(entity);

                entities.erase(entity);
                entities.insert({entity, {newPosition.x, newPosition.y}});
            }
            else
            {
                entity->SetDestination({-1, -1});
            }

            ++it;
        }
    }
}
