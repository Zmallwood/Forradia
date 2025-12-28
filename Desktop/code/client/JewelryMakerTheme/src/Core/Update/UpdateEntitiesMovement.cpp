/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "UpdateEntitiesMovement.hpp"
#include "WorldStructure/Entity.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/Common/General.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "Essentials/Player/Player.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto ensureEntityDestination(std::shared_ptr<Entity> entity, Point position) -> void
    {
        auto destination{entity->getDestination()};

        if (destination.x == -1 && destination.y == -1)
        {
            // NOLINTNEXTLINE(readability-magic-numbers)
            auto newDestinationX{position.x + getRandomInt(11) - 5};

            // NOLINTNEXTLINE(readability-magic-numbers)
            auto newDestinationY{position.y + getRandomInt(11) - 5};

            entity->setDestination({newDestinationX, newDestinationY});
        }
    }

    auto updateEntitiesMovement() -> void
    {
        auto worldArea{World::instance().getWorldArea(Player::instance().getWorldAreaCoordinate())};
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

            ensureEntityDestination(entity, position);

            auto deltaX{entity->getDestination().x - position.x};
            auto deltaY{entity->getDestination().y - position.y};

            auto normalizedDX{normalize(deltaX)};
            auto normalizedDY{normalize(deltaY)};

            auto newX{position.x + normalizedDX};
            auto newY{position.y + normalizedDY};

            Point newPosition{newX, newY};

            if (newPosition == entity->getDestination())
            {
                entity->setDestination({-1, -1});
            }

            auto tile{worldArea->getTile(newPosition.x, newPosition.y)};

            if (tile && !tile->getEntity() && tile->getGround() != hash("GroundWater"))
            {
                auto oldPosition{entities.at(entity)};

                entity->setTicksLastMovement(now);

                if (normalizedDX == 0 && normalizedDY < 0)
                {
                    entity->setDirection(Directions::North);
                }
                else if (normalizedDX > 0 && normalizedDY == 0)
                {
                    entity->setDirection(Directions::East);
                }
                else if (normalizedDX == 0 && normalizedDY > 0)
                {
                    entity->setDirection(Directions::South);
                }
                else if (normalizedDX < 0 && normalizedDY == 0)
                {
                    entity->setDirection(Directions::West);
                }
                else if (normalizedDX > 0 && normalizedDY < 0)
                {
                    entity->setDirection(Directions::NorthEast);
                }
                else if (normalizedDX > 0 && normalizedDY > 0)
                {
                    entity->setDirection(Directions::SouthEast);
                }
                else if (normalizedDX < 0 && normalizedDY > 0)
                {
                    entity->setDirection(Directions::SouthWest);
                }
                else if (normalizedDX < 0 && normalizedDY < 0)
                {
                    entity->setDirection(Directions::NorthWest);
                }

                auto oldTile{worldArea->getTile(oldPosition.x, oldPosition.y)};
                auto newTile{worldArea->getTile(newPosition.x, newPosition.y)};

                oldTile->setEntity(nullptr);
                newTile->setEntity(entity);

                entities.erase(entity);
                entities.insert({entity, {newPosition.x, newPosition.y}});
            }
            else
            {
                entity->setDestination({-1, -1});
            }

            ++it;
        }
    }
}
