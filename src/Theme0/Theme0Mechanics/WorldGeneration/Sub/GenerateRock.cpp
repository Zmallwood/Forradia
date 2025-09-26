/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateGrass.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"

namespace Forradia
{
    void GenerateRock()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto numRockAreas{30 + RandomInt(10)};

        for (auto i = 0; i < numRockAreas; i++)
        {
            auto xCenter{RandomInt(worldArea->GetSize().width)};
            auto yCenter{RandomInt(worldArea->GetSize().height)};
            auto radius{3 + RandomInt(10)};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto dx{x - xCenter};
                    auto dy{y - yCenter};

                    if (dx * dx + dy * dy <= radius * radius)
                    {
                        auto tile{worldArea->GetTile(x, y)};

                        if (tile->GetElevation() > 0)
                        {
                            tile->SetGround("GroundRock");
                        }
                    }
                }
            }
        }
    }
}