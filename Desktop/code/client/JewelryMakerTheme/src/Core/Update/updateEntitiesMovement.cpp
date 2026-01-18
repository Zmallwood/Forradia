/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "updateEntitiesMovement.hpp"
#include "WorldStructure/Entity.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/Common/General.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "Player/Player.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto ensureEntityDestination(const std::shared_ptr<Entity> &entity, const Point &position)
        -> void
    {
        auto destination{entity->getDestination()};

        If(destination.x == -1 && destination.y == -1)
        {
            // NOLINTNEXTLINE(readability-magic-numbers)
            auto newDestinationX{position.x + getRandomInt(11) - 5};

            // NOLINTNEXTLINE(readability-magic-numbers)
            auto newDestinationY{position.y + getRandomInt(11) - 5};

            entity->setDestination({newDestinationX, newDestinationY});
        }
    }

    auto getEntityNewPosition(const std::shared_ptr<Entity> &entity, const Point &position) -> Point
    {
        auto destination{entity->getDestination()};

        auto deltaX{destination.x - position.x};
        auto deltaY{destination.y - position.y};

        auto normalizedDX{normalize(deltaX)};
        auto normalizedDY{normalize(deltaY)};

        auto newX{position.x + normalizedDX};
        auto newY{position.y + normalizedDY};

        return {newX, newY};
    }

    auto setEntityDirection(const std::shared_ptr<Entity> &entity, const Point &oldPosition) -> void
    {
        auto destination{entity->getDestination()};

        auto deltaX{destination.x - oldPosition.x};
        auto deltaY{destination.y - oldPosition.y};

        If(deltaX == 0 && deltaY < 0)
        {
            entity->setDirection(Directions::North);
        }
        ElseIf(deltaX > 0 && deltaY == 0)
        {
            entity->setDirection(Directions::East);
        }
        ElseIf(deltaX == 0 && deltaY > 0)
        {
            entity->setDirection(Directions::South);
        }
        ElseIf(deltaX < 0 && deltaY == 0)
        {
            entity->setDirection(Directions::West);
        }
        ElseIf(deltaX > 0 && deltaY < 0)
        {
            entity->setDirection(Directions::NorthEast);
        }
        ElseIf(deltaX > 0 && deltaY > 0)
        {
            entity->setDirection(Directions::SouthEast);
        }
        ElseIf(deltaX < 0 && deltaY > 0)
        {
            entity->setDirection(Directions::SouthWest);
        }
        ElseIf(deltaX < 0 && deltaY < 0)
        {
            entity->setDirection(Directions::NorthWest);
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

            If(now < entity->getTicksLastMovement() + invertSpeed(entity->getMovementSpeed()))
            {
                ++it;

                continue;
            }

            ensureEntityDestination(entity, position);

            auto newPosition{getEntityNewPosition(entity, position)};

            If(newPosition == entity->getDestination())
            {
                entity->setDestination({-1, -1});
            }

            auto tile{worldArea->getTile(newPosition.x, newPosition.y)};

            If(tile && !tile->getEntity() && tile->getGround() != hash("GroundWater"))
            {
                auto oldPosition{entities.at(entity)};

                entity->setTicksLastMovement(now);

                setEntityDirection(entity, position);

                auto oldTile{worldArea->getTile(oldPosition.x, oldPosition.y)};
                auto newTile{worldArea->getTile(newPosition.x, newPosition.y)};

                oldTile->setEntity(nullptr);
                newTile->setEntity(entity);

                entities.erase(entity);
                entities.insert({entity, {newPosition.x, newPosition.y}});
            }
            Else
            {
                entity->setDestination({-1, -1});
            }

            ++it;
        }
    }
}
