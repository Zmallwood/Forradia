/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateRivers.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/World.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/WorldArea.hpp"
#include "Theme0/Theme0Mechanics/WorldStructure/Tile.hpp"

namespace Forradia
{
    void GenerateRivers()
    {
        auto worldArea{_<World>().GetCurrentWorldArea()};

        auto size{worldArea->GetSize()};

        auto numRivers{40 + RandomInt(10)};

        for (auto i = 0; i < numRivers; i++)
        {
            auto x{static_cast<float>(RandomInt(size.width))};
            auto y{static_cast<float>(RandomInt(size.height))};

            auto angle{RandomInt(360)};
            auto length{15 + RandomInt(40)};

            for (auto j = 0; j < length; j++)
            {
                auto xCoordinate{static_cast<int>(x)};
                auto yCoordinate{static_cast<int>(y)};

                if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
                {
                    continue;
                }

                auto tile = worldArea->GetTile(xCoordinate, yCoordinate);

                if (tile)
                {
                    tile->SetGround("GroundWater");
                }

                auto dx = std::cos(angle * M_PI / 180.0f);
                auto dy = std::sin(angle * M_PI / 180.0f);

                x += dx;
                y += dy;
            }
        }
    }
}