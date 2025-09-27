/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "UpdateCreatureMovement.hpp"
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

        for (auto it = creaturesMirrorRef.begin(); it != creaturesMirrorRef.end();)
        {
            auto creature{it->first};
            auto position{it->second};

            auto now{GetTicks()};

            if (creature->GetIsLeader())
            {
                if (now < creature->GetTicksLastMove() + InvertMovementSpeed(creature->GetMovementSpeed()))
                {
                    ++it;
                    continue;
                }

                auto destination{creature->GetDestination()};

                if (destination.x == -1 && destination.y == -1)
                {
                    auto newDestinationX{position.x + RandomInt(11) - 5};
                    auto newDestinationY{position.y + RandomInt(11) - 5};
                    creature->SetDestination({newDestinationX, newDestinationY});
                }

                auto dx{creature->GetDestination().x - position.x};
                auto dy{creature->GetDestination().y - position.y};

                auto normDx{0};
                auto normDy{0};

                auto absDx{std::abs(dx)};
                auto absDy{std::abs(dy)};

                if (dx)
                {
                    normDx = dx / absDx;
                }

                if (dy)
                {
                    normDy = dy / absDy;
                }

                auto newX{position.x + normDx};
                auto newY{position.y + normDy};

                if (newX == creature->GetDestination().x && newY == creature->GetDestination().y)
                {
                    creature->SetDestination({-1, -1});
                }

                auto tile{worldArea->GetTile(newX, newY)};

                if (tile && !tile->GetCreature() && tile->GetGround() != Hash("GroundWater"))
                {
                    creature->SetTicksLastMove(now);
                    auto oldTile{worldArea->GetTile(position.x, position.y)};
                    oldTile->SetCreature(nullptr);
                    tile->SetCreature(creature);
                    creaturesMirrorRef.erase(it);
                    creaturesMirrorRef.insert({creature, {newX, newY}});

                    ++it;
                    continue;
                }
                else
                {
                    creature->SetDestination({-1, -1});
                    ++it;
                    continue;
                }
            }
            else
            {
                if (now < creature->GetTicksLastMove() + InvertMovementSpeed(creature->GetMovementSpeed()))
                {
                    ++it;
                    continue;
                }

                auto leader{creature->GetLeader()};
                if (leader)
                {
                    if (now < creature->GetTicksLastMove() + InvertMovementSpeed(creature->GetMovementSpeed()))
                    {
                        ++it;
                        continue;
                    }

                    auto leaderPositionIt = creaturesMirrorRef.find(leader);
                    if (leaderPositionIt != creaturesMirrorRef.end())
                    {
                        auto leaderPosition{leaderPositionIt->second};
                        auto offsetLeader{creature->GetOffsetLeader()};
                        auto targetX{leaderPosition.x + offsetLeader.x};
                        auto targetY{leaderPosition.y + offsetLeader.y};

                        auto dx = targetX - position.x;
                        auto dy = targetY - position.y;

                        auto normDx{0};
                        auto normDy{0};

                        auto absDx{std::abs(dx)};
                        auto absDy{std::abs(dy)};

                        if (dx)
                        {
                            normDx = dx / absDx;
                        }

                        if (dy)
                        {
                            normDy = dy / absDy;
                        }

                        if (normDx == 0 && normDy == 0)
                        {
                            ++it;
                            continue;
                        }

                        auto newX{position.x + normDx};
                        auto newY{position.y + normDy};

                        auto tile{worldArea->GetTile(newX, newY)};

                        if (tile && !tile->GetCreature() && tile->GetGround() != Hash("GroundWater"))
                        {
                            creature->SetTicksLastMove(now);
                            auto oldTile{worldArea->GetTile(position.x, position.y)};
                            oldTile->SetCreature(nullptr);
                            tile->SetCreature(creature);
                            creaturesMirrorRef.erase(it);
                            creaturesMirrorRef.insert({creature, {newX, newY}});
                            ++it;
                            continue;
                        }
                    }
                }
            }
            ++it;
        }
    }
}