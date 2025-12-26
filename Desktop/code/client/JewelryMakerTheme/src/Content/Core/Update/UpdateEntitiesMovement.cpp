/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "UpdateEntitiesMovement.hpp"
    #include "Content/WorldStructure/Entity.hpp"
    #include "Content/WorldStructure/Tile.hpp"
    #include "Content/WorldStructure/World.hpp"
    #include "Content/WorldStructure/WorldArea.hpp" 
    #include "ForradiaEngine/Common/General.hpp"
    #include "ForradiaEngine/Common/Utilities.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto updateEntitiesMovement() -> void
    {
        auto worldArea{World::instance().getCurrentWorldArea()};
        auto &entities{worldArea->getEntitiesMirrorRef()};

        auto now{getTicks()};

        for (auto it = entities.begin(); it != entities.end();)
        {
            auto entity{it->first};
            auto position{it->second};

            if (now < entity->getTicksLastMovement() + invertSpeed(entity->getMovementSpeed()))
            {
                ++it;

                continue;
            }

            auto destination{entity->getDestination()};

            if (destination.x == -1 && destination.y == -1)
            {
                // NOLINTNEXTLINE(readability-magic-numbers)
                auto newDestinationX{position.x + getRandomInt(11) - 5};

                // NOLINTNEXTLINE(readability-magic-numbers)
                auto newDestinationY{position.y + getRandomInt(11) - 5};

                entity->setDestination({newDestinationX, newDestinationY});
            }

            /* Calculate the new position */ // clang-format off
                auto deltaX{entity->getDestination().x - position.x};
                auto deltaY{entity->getDestination().y - position.y};

                auto normalizedDX{normalize(deltaX)};
                auto normalizedDY{normalize(deltaY)};

                auto newX{position.x + normalizedDX};
                auto newY{position.y + normalizedDY};

                Point newPosition{newX, newY};
            // clang-format on

            if (newPosition == entity->getDestination())
            {
                entity->setDestination({-1, -1});
            }

            auto tile{worldArea->getTile(newPosition.x, newPosition.y)};

            if (tile && !tile->getEntity() && tile->getGround() != hash("GroundWater"))
            {
                /* Move entity to the new tile */ // clang-format off
                    auto oldPosition{entities.at(entity)};

                    entity->setTicksLastMovement(now);

                    auto oldTile{worldArea->getTile(oldPosition.x, oldPosition.y)};
                    auto newTile{worldArea->getTile(newPosition.x, newPosition.y)};

                    oldTile->setEntity(nullptr);
                    newTile->setEntity(entity);

                    entities.erase(entity);
                    entities.insert({entity, {newPosition.x, newPosition.y}});
                // clang-format on
            }
            else
            {
                entity->setDestination({-1, -1});
            }

            ++it;
        }
    }
}
