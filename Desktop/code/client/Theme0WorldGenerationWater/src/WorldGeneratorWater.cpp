/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorWater.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    auto WorldGeneratorWater::generateWater() const -> void
    {
        generateNaturalRivers();
        generateLakesInValleys();
    }

    auto WorldGeneratorWater::generateNaturalRivers() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};

        auto numRivers{150 + getRandomInt(100)};

        for (auto i = 0; i < numRivers; i++)
        {
            auto attempts{0};
            auto startX{0};
            auto startY{0};
            auto foundStart{false};

            // Vary starting elevations - some high, some medium, some low.
            auto elevationType{getRandomInt(100)};

            auto minElevation{0};

            if (elevationType < 40)
            {
                // 40% start from high elevation.
                minElevation = 50;
            }
            else if (elevationType < 70)
            {
                // 30% start from medium elevation.
                minElevation = 20;
            }
            else
            {
                // 30% start from lower elevation.
                minElevation = 5;
            }

            // Find a starting point.
            while (attempts < 100 && !foundStart)
            {
                startX = getRandomInt(worldAreaSize.width);
                startY = getRandomInt(worldAreaSize.height);

                auto tile{worldArea->getTile(startX, startY)};

                // If the tile is found and the elevation is greater than the minimum elevation,
                // and the tile is a valid water placement location.
                if (tile && tile->getElevation() > minElevation && isValidForWater(startX, startY))
                {
                    foundStart = true;
                }

                attempts++;
            }

            if (!foundStart)
            {
                // Just continue to the next river.
                continue;
            }

            auto startElevation{worldArea->getTile(startX, startY)->getElevation()};
            auto baseLength{40};
            auto lengthVariation{60};

            if (startElevation > 40)
            {
                // Increase the base length and the length variation.
                baseLength = 60;
                lengthVariation = 80;
            }
            else if (startElevation > 15)
            {
                // Increase the base length and the length variation.
                baseLength = 50;
                lengthVariation = 70;
            }

            auto length{baseLength + getRandomInt(lengthVariation)};

            generateRiverFromSource(startX, startY, length);
        }
    }

    auto WorldGeneratorWater::generateLakesInValleys() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};
        auto worldScaling{getWorldScaling()};
        auto numLakes{12 + getRandomInt(8)};

        for (auto i = 0; i < numLakes; i++)
        {
            auto attempts{0};
            auto centerX{0};
            auto centerY{0};

            auto foundLocation{false};

            // Find a suitable valley location.
            while (attempts < 50 && !foundLocation)
            {
                centerX = getRandomInt(worldAreaSize.width);
                centerY = getRandomInt(worldAreaSize.height);

                auto tile{worldArea->getTile(centerX, centerY)};

                if (tile && tile->getElevation() <= 32 && tile->getGround() != hash("GroundWater"))
                {
                    // Set the flag to indicate that we found a suitable valley location.
                    foundLocation = true;
                }

                attempts++;
            }

            if (!foundLocation)
            {
                // Just continue to the next lake.
                continue;
            }

            auto radius{static_cast<int>(
                3 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(6 * worldScaling))))};

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    if (!worldArea->isValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto tile{worldArea->getTile(x, y)};

                    if (!tile)
                    {
                        // Just continue to the next tile.
                        continue;
                    }

                    if (!isValidForWater(x, y))
                    {
                        // Just continue to the next tile.
                        continue;
                    }

                    auto distance{getDistance(x, y, centerX, centerY)};

                    if (distance * distance <= static_cast<float>(radius * radius))
                    {
                        tile->setGround("GroundWater");

                        auto depth{static_cast<int>((1.0F - distance / static_cast<float>(radius)) *
                                                    4.0F) +
                                   1};

                        tile->setWaterDepth(depth);
                        tile->setElevation(0);

                        setAdjacentTilesElevationToZero(x, y);
                    }
                }
            }
        }
    }

    auto WorldGeneratorWater::isValidForWater(int x, int y) const -> bool
    {
        if (!getWorldArea()->isValidCoordinate(x, y))
        {
            return false;
        }

        auto tile{getWorldArea()->getTile(x, y)};

        if (!tile)
        {
            return false;
        }

        return tile->getElevation() < 80;
    }
    auto WorldGeneratorWater::setAdjacentTilesElevationToZero(int x, int y) const -> void
    {
        // Set elevation to 0 for all tiles adjacent to a water tile.
        // This creates a shoreline effect where land around water is at sea level.

        // Enumerate all eight surrounding directions for neighbor checks.

        // Visit each neighboring tile and update elevation when needed.
        for (auto dir = 0; dir < 8; dir++)
        {
            // clang-format off
            int directions[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                 {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
            // clang-format on

            auto adjacentX{x + directions[dir][0]};
            auto adjacentY{y + directions[dir][1]};

            if (!getWorldArea()->isValidCoordinate(adjacentX, adjacentY))
            {
                continue;
            }

            auto adjacentTile{getWorldArea()->getTile(adjacentX, adjacentY)};

            if (!adjacentTile)
            {
                continue;
            }

            if (adjacentTile->getGround() != hash("GroundWater"))
            {
                adjacentTile->setElevation(0);
            }
        }
    }
}
