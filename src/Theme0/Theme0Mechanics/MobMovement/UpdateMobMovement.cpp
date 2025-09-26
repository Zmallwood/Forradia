#include "UpdateMobMovement.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Mob.hpp"

namespace Forradia
{
    void UpdateMobMovement()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto &mobsMirrorRef{worldArea->GetMobsMirrorRef()};

        for (auto it = mobsMirrorRef.begin(); it != mobsMirrorRef.end();)
        {
            auto mob{it->first};
            auto position{it->second};

            auto now{GetTicks()};

            if (mob->GetIsLeader())
            {
                if (now < mob->GetTicksLastMove() + InvertMovementSpeed(mob->GetMovementSpeed()))
                {
                    ++it;
                    continue;
                }

                auto destination{mob->GetDestination()};

                if (destination.x == -1 && destination.y == -1)
                {
                    auto newDestinationX{position.x + RandomInt(11) - 5};
                    auto newDestinationY{position.y + RandomInt(11) - 5};
                    mob->SetDestination({newDestinationX, newDestinationY});
                }

                auto dx{mob->GetDestination().x - position.x};
                auto dy{mob->GetDestination().y - position.y};

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

                if (newX == mob->GetDestination().x && newY == mob->GetDestination().y)
                {
                    mob->SetDestination({-1, -1});
                }

                auto tile{worldArea->GetTile(newX, newY)};

                if (tile && !tile->GetMob() && tile->GetGround() != Hash("GroundWater"))
                {
                    mob->SetTicksLastMove(now);
                    auto oldTile{worldArea->GetTile(position.x, position.y)};
                    oldTile->SetMob(nullptr);
                    tile->SetMob(mob);
                    mobsMirrorRef.erase(it);
                    mobsMirrorRef.insert({mob, {newX, newY}});

                    ++it;
                    continue;
                }
                else
                {
                    mob->SetDestination({-1, -1});
                    ++it;
                    continue;
                }
            }
            else
            {
                if (now < mob->GetTicksLastMove() + InvertMovementSpeed(mob->GetMovementSpeed()))
                {
                    ++it;
                    continue;
                }

                auto leader{mob->GetLeader()};
                if (leader)
                {
                    if (now < mob->GetTicksLastMove() + InvertMovementSpeed(mob->GetMovementSpeed()))
                    {
                        ++it;
                        continue;
                    }

                    auto leaderPositionIt = mobsMirrorRef.find(leader);
                    if (leaderPositionIt != mobsMirrorRef.end())
                    {
                        auto leaderPosition{leaderPositionIt->second};
                        auto offsetLeader{mob->GetOffsetLeader()};
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

                        if (tile && !tile->GetMob() && tile->GetGround() != Hash("GroundWater"))
                        {
                            mob->SetTicksLastMove(now);
                            auto oldTile{worldArea->GetTile(position.x, position.y)};
                            oldTile->SetMob(nullptr);
                            tile->SetMob(mob);
                            mobsMirrorRef.erase(it);
                            mobsMirrorRef.insert({mob, {newX, newY}});
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