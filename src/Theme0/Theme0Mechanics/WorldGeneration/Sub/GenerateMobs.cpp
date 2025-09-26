/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateMobs.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Mob.hpp"

namespace Forradia
{
    void GenerateMobs()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        auto numRatGroups{20 + RandomInt(5)};

        for (auto i = 0; i < numRatGroups; i++)
        {
            auto xCenter{RandomInt(size.width)};
            auto yCenter{RandomInt(size.height)};
            auto radius{3 + RandomInt(3)};

            auto tileCenter{worldArea->GetTile(xCenter, yCenter)};

            auto newLeader = std::make_shared<Mob>("MobRatKing");
            newLeader->SetIsLeader(true);
            tileCenter->SetMob(newLeader);
            worldArea->GetMobsMirrorRef().insert({tileCenter->GetMob(), {xCenter, yCenter}});

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    auto dx{x - xCenter};
                    auto dy{y - yCenter};

                    if (dx * dx + dy * dy <= radius * radius && dx * dx + dy * dy >= (radius - 1) * (radius - 1))
                    {
                        auto tile{worldArea->GetTile(x, y)};

                        if (tile && !tile->GetMob())
                        {
                            auto newMinion = std::make_shared<Mob>("MobRat");
                            newMinion->SetLeader(newLeader);
                            newMinion->SetOffsetLeader({dx, dy});
                            tile->SetMob(newMinion);
                            worldArea->GetMobsMirrorRef().insert({tile->GetMob(), {x, y}});
                        }
                    }
                }
            }
        }
    }
}