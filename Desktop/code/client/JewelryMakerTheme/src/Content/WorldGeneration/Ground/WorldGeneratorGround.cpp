/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorGround.hpp"

#include "Content/WorldStructure/Tile.hpp"
#include "Content/WorldStructure/WorldArea.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorGround::generateGroundWithElevation() const -> void
    {
        clearWithDirt();
        generateElevationWithBiomes();
        generateMountainRanges();
        generateValleys();
        generateGrassBiomes();
        generateRockFormations();
    }

    auto WorldGeneratorGround::clearWithDirt() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};

        for (auto y = 0; y < worldAreaSize.height; y++)
        {
            for (auto x = 0; x < worldAreaSize.width; x++)
            {
                auto tile{worldArea->getTile(x, y)};

                if (!tile)
                {
                    continue;
                }

                tile->setGround("GroundDirt");
                tile->setElevation(getDefaultGroundElevation());
            }
        }
    }

    auto WorldGeneratorGround::getMaxElevation() -> int
    {
        // Maximum elevation cap to prevent excessive stacking.
        return 300;
    }

    auto WorldGeneratorGround::getMaxSlopePerTile() -> int
    {
        // Maximum elevation difference between adjacent tiles.
        // This prevents mountains from becoming too steep.
        return 8;
    }

    auto WorldGeneratorGround::getMaxAllowedElevation(int x, int y, int currentElevation) const
        -> int
    {
        // Calculate the maximum elevation this tile can have based on adjacent tiles
        // to prevent steep slopes. This ensures mountains have gradual slopes.

        auto maxSlope{getMaxSlopePerTile()};

        // Start with allowing max slope increase from current elevation
        auto maxAllowedElevation{currentElevation + maxSlope};

        // Check all 8 adjacent tiles (including diagonals) to ensure we don't create too steep
        // a slope.

        for (auto dir = 0; dir < 8; dir++)
        {
            int directions[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                 {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

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

            // Skip water tiles - they have their own elevation rules (set to 0).
            if (adjacentTile->getGround() == hash("GroundWater"))
            {
                continue;
            }

            auto adjacentElevation{adjacentTile->getElevation()};

            // The new elevation should not exceed adjacent tile elevation + max slope.
            // This prevents creating a steep upward slope from the adjacent tile.

            auto maxFromAdjacent{adjacentElevation + maxSlope};

            // Update the maximum allowed elevation if the adjacent tile elevation is lower.
            if (maxFromAdjacent < maxAllowedElevation)
            {
                maxAllowedElevation = maxFromAdjacent;
            }
        }

        return maxAllowedElevation;
    }

    auto WorldGeneratorGround::clampElevation(int elevation) -> int
    {
        auto maxElevation{getMaxElevation()};

        if (elevation > maxElevation)
        {
            return maxElevation;
        }

        if (elevation < getDefaultGroundElevation())
        {
            return getDefaultGroundElevation();
        }

        return elevation;
    }
}
