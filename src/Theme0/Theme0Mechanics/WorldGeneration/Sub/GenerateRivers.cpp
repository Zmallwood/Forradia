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

        auto numRivers{20 + RandomInt(10)};

        for (auto i = 0; i < numRivers; i++)
        {
            auto x{static_cast<float>(RandomInt(size.width))};
            auto y{static_cast<float>(RandomInt(size.height))};

            auto startAngle{RandomInt(360)};
            auto length{25 + RandomInt(40)};

            auto prevXCoordinate{-1};
            auto prevYCoordinate{-1};

            for (auto j = 0; j < length; j++)
            {
                auto angle {startAngle + std::sin(j*M_PI/10.0f)*45};

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

                if (xCoordinate != prevXCoordinate && yCoordinate != prevYCoordinate && prevXCoordinate != -1 && prevYCoordinate != -1)
                {
                    if (xCoordinate < prevXCoordinate)
                    {
                        auto tileAdjacentEast{worldArea->GetTile(xCoordinate + 1, yCoordinate)};

                        if (tileAdjacentEast)
                        {
                            tileAdjacentEast->SetGround("GroundWater");
                        }
                    }
                    else
                    {
                        auto tileAdjacentWest{worldArea->GetTile(xCoordinate - 1, yCoordinate)};

                        if (tileAdjacentWest)
                        {
                            tileAdjacentWest->SetGround("GroundWater");
                        }
                    }
                }

                auto dx = std::cos(angle * M_PI / 180.0f);
                auto dy = std::sin(angle * M_PI / 180.0f);

                x += dx;
                y += dy;

                prevXCoordinate = xCoordinate;
                prevYCoordinate = yCoordinate;
            }
        }
    }
}