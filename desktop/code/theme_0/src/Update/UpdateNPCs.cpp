//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TileHovering.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "NPC.hpp"

#include "GUICore/GUIChatBox.hpp"

#include "NumbersUtilities.hpp"

namespace Forradia
{
    namespace Theme0
    {
        namespace GameplayCore
        {
            void UpdateNPCs()
            {
                auto worldArea{
                    _<World>().GetCurrentWorldArea()};

                auto &npcs{worldArea->GetNPCsMirrorRef()};

                auto now{GetTicks()};

                for (auto it = npcs.begin();
                     it != npcs.end();)
                {
                    auto npc{it->first};

                    auto position{it->second};

                    if (now >
                        npc->GetTicksNextSpontaneousSpeech())
                    {
                        auto name{npc->GetName()};

                        if (GetRandomInt(20) == 0)
                        {
                            _<GUIChatBox>().Print(
                                name +
                                ": Buying blueberries, "
                                "one gold each.");
                        }
                        else
                        {
                            _<GUIChatBox>().Print(
                                name + ": Hello all!");
                        }

                        npc->SetTicksNextSpontaneousSpeech(
                            now + 5 * k_oneSecMillis +
                            (6000 * k_oneSecMillis));
                    }
                    if (now <
                        npc->GetTicksLastMovement() +
                            InvertMovementSpeed(
                                npc->GetMovementSpeed()))
                    {
                        ++it;

                        continue;
                    }

                    auto destination{npc->GetDestination()};

                    if (destination.x == -1 &&
                        destination.y == -1)
                    {
                        auto newDestinationX{
                            position.x + GetRandomInt(11) -
                            5};
                        auto newDestinationY{
                            position.y + GetRandomInt(11) -
                            5};

                        npc->SetDestination(
                            {newDestinationX,
                             newDestinationY});
                    }

                    auto dX{npc->GetDestination().x -
                            position.x};

                    auto dY{npc->GetDestination().y -
                            position.y};

                    auto normalizedDX{Normalize(dX)};

                    auto normalizedDY{Normalize(dY)};

                    auto newX{position.x + normalizedDX};

                    auto newY{position.y + normalizedDY};

                    auto newPosition{Point{newX, newY}};

                    if (newPosition ==
                        npc->GetDestination())
                    {
                        npc->SetDestination({-1, -1});
                    }

                    auto tile{worldArea->GetTile(
                        newPosition.x, newPosition.y)};

                    if (tile && !tile->GetNPC() &&
                        tile->GetGround() !=
                            Hash("ground_water"))
                    {
                        auto oldPosition{position};

                        npc->SetTicksLastMovement(now);

                        auto oldTile{worldArea->GetTile(
                            oldPosition.x, oldPosition.y)};

                        auto newTile{worldArea->GetTile(
                            newPosition.x, newPosition.y)};

                        oldTile->SetNPC(nullptr);

                        newTile->SetNPC(npc);

                        npcs.erase(npc);

                        npcs.insert({npc,
                                     {newPosition.x,
                                      newPosition.y}});
                    }
                    else
                    {
                        npc->SetDestination({-1, -1});
                    }

                    ++it;
                }
            }
        }
    }
}