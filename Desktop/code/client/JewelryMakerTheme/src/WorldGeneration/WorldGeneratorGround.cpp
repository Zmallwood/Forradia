/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorGround.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorGround::generateGroundWithElevation() -> void
    {
        clearWithDirt();
        generateElevationWithBiomes();
        generateMountainRanges();
        generateValleys();
        generateGrassBiomes();
        generateRockFormations();
    }

    auto WorldGeneratorGround::clearWithDirt() -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};

        for (auto yPos = 0; yPos < worldAreaSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < worldAreaSize.width; xPos++)
            {
                auto tile{worldArea->getTile(xPos, yPos)};

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
        // NOLINTNEXTLINE(readability-magic-numbers)
        return 300;
    }

    auto WorldGeneratorGround::getMaxSlopePerTile() -> int
    {
        // Maximum elevation difference between adjacent tiles.
        // This prevents mountains from becoming too steep.
        // NOLINTNEXTLINE(readability-magic-numbers)
        return 8;
    }

    auto WorldGeneratorGround::getMaxAllowedElevation(int xPos, int yPos, int currentElevation)
        -> int
    {
        // Calculate the maximum elevation this tile can have based on adjacent tiles
        // to prevent steep slopes. This ensures mountains have gradual slopes.

        auto maxSlope{getMaxSlopePerTile()};

        // Start with allowing max slope increase from current elevation
        auto maxAllowedElevation{currentElevation + maxSlope};

        // Check all 8 adjacent tiles (including diagonals) to ensure we don't create too steep
        // a slope.

        std::vector<Point> directions{{Point{-1, -1}, Point{0, -1}, Point{1, -1}, Point{-1, 0},
                                       Point{1, 0}, Point{-1, 1}, Point{0, 1}, Point{1, 1}}};

        for (const auto &direction : directions)
        {
            auto adjacentX{xPos + direction.x};
            auto adjacentY{yPos + direction.y};

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
