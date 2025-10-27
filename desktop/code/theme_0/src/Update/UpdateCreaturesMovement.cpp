//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TileHovering.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "Creature.hpp"

#include "NumbersUtilities.hpp"

namespace Forradia
{
    namespace Theme0
    {
        namespace GameplayCore
        {
            void UpdateCreaturesMovement()
            {
                auto worldArea{
                    _<World>().GetCurrentWorldArea()};

                auto &creatures{
                    worldArea->GetCreaturesMirrorRef()};

                auto now{GetTicks()};

                for (auto it = creatures.begin();
                     it != creatures.end();)
                {
                    auto creature{it->first};

                    auto position{it->second};

                    if (now <
                        creature->GetTicksLastMovement() +
                            InvertMovementSpeed(
                                creature
                                    ->GetMovementSpeed()))
                    {
                        ++it;

                        continue;
                    }

                    auto destination{
                        creature->GetDestination()};

                    if (destination.x == -1 &&
                        destination.y == -1)
                    {
                        auto newDestination{
                            position.x + GetRandomInt(11) -
                            5};

                        auto newDestinationY{
                            position.y + GetRandomInt(11) -
                            5};

                        creature->SetDestination(
                            {newDestination,
                             newDestinationY});
                    }

                    auto worldArea{
                        _<World>().GetCurrentWorldArea()};

                    auto &creatures{
                        worldArea->GetCreaturesMirrorRef()};

                    auto dX{creature->GetDestination().x -
                            position.x};

                    auto dY{creature->GetDestination().y -
                            position.y};

                    auto normalizedDX{Normalize(dX)};

                    auto normalizedDY{Normalize(dY)};

                    auto newX{position.x + normalizedDX};

                    auto newY{position.y + normalizedDY};

                    Point newPosition{newX, newY};

                    if (newPosition ==
                        creature->GetDestination())
                    {
                        creature->SetDestination({-1, -1});
                    }

                    auto tile{worldArea->GetTile(
                        newPosition.x, newPosition.y)};

                    if (tile && !tile->GetCreature() &&
                        tile->GetGround() !=
                            Hash("ground_water"))
                    {
                        auto oldPosition{
                            creatures.at(creature)};

                        creature->SetTicksLastMovement(now);

                        auto oldTile{worldArea->GetTile(
                            oldPosition.x, oldPosition.y)};

                        auto newTile{worldArea->GetTile(
                            newPosition.x, newPosition.y)};

                        oldTile->SetCreature(nullptr);

                        newTile->SetCreature(creature);

                        creatures.erase(creature);

                        creatures.insert({creature,
                                          {newPosition.x,
                                           newPosition.y}});
                    }
                    else
                    {
                        creature->SetDestination({-1, -1});
                    }

                    ++it;
                }
            }
        }
    }
}