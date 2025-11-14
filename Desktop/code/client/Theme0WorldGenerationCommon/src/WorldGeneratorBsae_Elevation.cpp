//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorBase.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    int WorldGeneratorBase::GetMaxElevation() const
    {
        // Maximum elevation cap to prevent excessive stacking.

        return 300;
    }

    int WorldGeneratorBase::GetMaxSlopePerTile() const
    {
        // Maximum elevation difference between adjacent tiles.
        // This prevents mountains from becoming too steep.

        return 8;
    }

    int WorldGeneratorBase::GetMaxAllowedElevation(int x, int y, int currentElevation) const
    {
        // Calculate the maximum elevation this tile can have based on adjacent tiles
        // to prevent steep slopes. This ensures mountains have gradual slopes.

        auto maxSlope{GetMaxSlopePerTile()};

        // Start with allowing max slope increase from current elevation

        auto maxAllowedElevation{currentElevation + maxSlope};

        // Check all 8 adjacent tiles (including diagonals) to ensure we don't create too steep a
        // slope.

        int directions[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

        for (auto dir = 0; dir < 8; dir++)
        {
            auto adjX{x + directions[dir][0]};

            auto adjY{y + directions[dir][1]};

            if (!m_worldArea->IsValidCoordinate(adjX, adjY))
            {
                continue;
            }

            auto adjTile{m_worldArea->GetTile(adjX, adjY)};

            if (!adjTile)
            {
                continue;
            }

            // Skip water tiles - they have their own elevation rules (set to 0).

            if (adjTile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            auto adjElevation{adjTile->GetElevation()};

            // The new elevation should not exceed adjacent tile elevation + max slope.
            // This prevents creating a steep upward slope from the adjacent tile.

            auto maxFromAdjacent{adjElevation + maxSlope};

            if (maxFromAdjacent < maxAllowedElevation)
            {
                maxAllowedElevation = maxFromAdjacent;
            }
        }

        return maxAllowedElevation;
    }

    int WorldGeneratorBase::ClampElevation(int elevation) const
    {
        auto maxElev{GetMaxElevation()};

        if (elevation > maxElev)
        {
            return maxElev;
        }

        if (elevation < k_defaultGroundElevation)
        {
            return k_defaultGroundElevation;
        }

        return elevation;
    }
}