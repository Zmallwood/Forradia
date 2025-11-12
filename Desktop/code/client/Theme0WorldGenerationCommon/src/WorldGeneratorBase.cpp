//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorBase.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Theme0Properties.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorBase::Prepare()
    {
        m_worldArea = _<Theme0::World>().GetCurrentWorldArea();

        m_size = m_worldArea->GetSize();

        m_scale = _<Theme0::Theme0Properties>().GetWorldScaling();
    }

    float WorldGeneratorBase::GetDistance(int x1, int y1, int x2, int y2) const
    {
        auto dx = static_cast<float>(x2 - x1);

        auto dy = static_cast<float>(y2 - y1);

        return std::sqrt(dx * dx + dy * dy);
    }

    int WorldGeneratorBase::GetElevationAt(int x, int y) const
    {
        if (!m_worldArea->IsValidCoordinate(x, y))
        {
            return 0;
        }

        auto tile = m_worldArea->GetTile(x, y);

        return tile ? tile->GetElevation() : 0;
    }

    bool WorldGeneratorBase::IsValidForWater(int x, int y) const
    {
        if (!m_worldArea->IsValidCoordinate(x, y))
        {
            return false;
        }

        auto tile = m_worldArea->GetTile(x, y);

        if (!tile)
        {
            return false;
        }

        // Don't place water on high elevation (mountains).

        return tile->GetElevation() < 80;
    }

    bool WorldGeneratorBase::IsValidForTree(int x, int y) const
    {
        if (!m_worldArea->IsValidCoordinate(x, y))
        {
            return false;
        }

        auto tile = m_worldArea->GetTile(x, y);
        if (!tile)
        {
            return false;
        }

        // Trees can't grow in water or on bare rock

        auto ground = tile->GetGround();

        return ground != Hash("GroundWater") && ground != Hash("GroundRock") &&
               tile->GetWaterDepth() == 0;
    }

    bool WorldGeneratorBase::IsNearWater(int x, int y, int radius) const
    {
        for (auto checkY = y - radius; checkY <= y + radius; checkY++)
        {
            for (auto checkX = x - radius; checkX <= x + radius; checkX++)
            {
                if (!m_worldArea->IsValidCoordinate(checkX, checkY))
                {
                    continue;
                }

                auto tile = m_worldArea->GetTile(checkX, checkY);

                if (tile && tile->GetGround() == Hash("GroundWater"))
                {
                    auto distance = GetDistance(x, y, checkX, checkY);

                    if (distance <= radius)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool WorldGeneratorBase::IsAdjacentToWater(int x, int y) const
    {
        // Check all 8 adjacent tiles (including diagonals) for water.

        int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

        for (auto dir = 0; dir < 8; dir++)
        {
            auto adjX = x + directions[dir][0];

            auto adjY = y + directions[dir][1];

            if (!m_worldArea->IsValidCoordinate(adjX, adjY))
            {
                continue;
            }

            auto adjTile = m_worldArea->GetTile(adjX, adjY);

            if (adjTile && adjTile->GetGround() == Hash("GroundWater"))
            {
                return true;
            }
        }

        return false;
    }

    void WorldGeneratorBase::CreateBiomeCluster(int centerX, int centerY, int radius,
                                                const char *groundType, float density) const
    {
        for (auto y = centerY - radius; y <= centerY + radius; y++)
        {
            for (auto x = centerX - radius; x <= centerX + radius; x++)
            {
                if (!m_worldArea->IsValidCoordinate(x, y))
                {
                    continue;
                }

                auto distance = GetDistance(x, y, centerX, centerY);

                if (distance > radius)
                {
                    continue;
                }

                // Create falloff effect - edges are less likely to have the biome.

                auto normalizedDistance = distance / radius;

                auto probability = (1.0f - normalizedDistance) * density;

                if (GetRandomInt(1000) < static_cast<int>(probability * 1000.0f))
                {
                    auto tile = m_worldArea->GetTile(x, y);

                    if (tile)
                    {
                        tile->SetGround(groundType);
                    }
                }
            }
        }
    }

    void WorldGeneratorBase::SetAdjacentTilesElevationToZero(int x, int y) const
    {
        // Set elevation to 0 for all tiles adjacent to a water tile.
        // This creates a shoreline effect where land around water is at sea level.

        int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

        for (auto dir = 0; dir < 8; dir++)
        {
            auto adjX = x + directions[dir][0];

            auto adjY = y + directions[dir][1];

            if (!m_worldArea->IsValidCoordinate(adjX, adjY))
            {
                continue;
            }

            auto adjTile = m_worldArea->GetTile(adjX, adjY);

            if (!adjTile)
            {
                continue;
            }

            // Only set elevation to 0 for non-water tiles (shoreline).

            if (adjTile->GetGround() != Hash("GroundWater"))
            {
                adjTile->SetElevation(0);
            }
        }
    }

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

        auto maxSlope = GetMaxSlopePerTile();

        // Start with allowing max slope increase from current elevation

        int maxAllowedElevation = currentElevation + maxSlope;

        // Check all 8 adjacent tiles (including diagonals) to ensure we don't create too steep a
        // slope.

        int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

        for (auto dir = 0; dir < 8; dir++)
        {
            auto adjX = x + directions[dir][0];

            auto adjY = y + directions[dir][1];

            if (!m_worldArea->IsValidCoordinate(adjX, adjY))
            {
                continue;
            }

            auto adjTile = m_worldArea->GetTile(adjX, adjY);

            if (!adjTile)
            {
                continue;
            }

            // Skip water tiles - they have their own elevation rules (set to 0).

            if (adjTile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            auto adjElevation = adjTile->GetElevation();

            // The new elevation should not exceed adjacent tile elevation + max slope.
            // This prevents creating a steep upward slope from the adjacent tile.

            auto maxFromAdjacent = adjElevation + maxSlope;

            if (maxFromAdjacent < maxAllowedElevation)
            {
                maxAllowedElevation = maxFromAdjacent;
            }
        }

        return maxAllowedElevation;
    }

    int WorldGeneratorBase::ClampElevation(int elevation) const
    {
        auto maxElev = GetMaxElevation();

        if (elevation > maxElev)
        {
            return maxElev;
        }

        if (elevation < 0)
        {
            return 0;
        }

        return elevation;
    }

    void WorldGeneratorBase::CreateElevationHill(int centerX, int centerY, int radius,
                                                 int maxElevation) const
    {
        for (auto y = centerY - radius; y <= centerY + radius; y++)
        {
            for (auto x = centerX - radius; x <= centerX + radius; x++)
            {
                if (!m_worldArea->IsValidCoordinate(x, y))
                {
                    continue;
                }

                auto distance = GetDistance(x, y, centerX, centerY);

                if (distance > radius)
                {
                    continue;
                }

                auto tile = m_worldArea->GetTile(x, y);

                if (!tile)
                {
                    continue;
                }

                // Skip water tiles.

                if (tile->GetGround() == Hash("GroundWater"))
                {
                    continue;
                }

                // Check current elevation for smooth capping.

                auto currentElevation = tile->GetElevation();

                auto maxElev = GetMaxElevation();

                // Skip if already at maximum.

                if (currentElevation >= maxElev)
                {
                    continue;
                }

                // Create smooth elevation based on distance.

                auto normalizedDistance = distance / radius;

                auto baseElevationGain = static_cast<float>(
                    (1.0f - normalizedDistance * normalizedDistance) * maxElevation);

                // Apply smooth falloff as we approach the elevation cap.
                // Start reducing gain when we're above 60% of max elevation for smoother
                // transition.

                auto elevationRatio =
                    static_cast<float>(currentElevation) / static_cast<float>(maxElev);

                auto falloffStart = 0.6f; // Start falloff at 60 % of max elevation

                float smoothScale = 1.0f;

                if (elevationRatio >= falloffStart)
                {
                    // Smooth falloff using a smoothstep-like curve for very gradual transition.
                    // When at falloffStart (60%), scale is 1.0.
                    // When at 1.0 (100%), scale is 0.0.

                    auto falloffRange = 1.0f - falloffStart;

                    auto t = (elevationRatio - falloffStart) / falloffRange; // t goes from 0 to 1

                    // Use smoothstep curve: 3t^2 - 2t^3 for smooth S-curve transition.
                    // This gives a smoother, more natural falloff.

                    smoothScale = 1.0f - (t * t * (3.0f - 2.0f * t));
                }

                // Apply smooth scaling to elevation gain.

                auto elevationGain = static_cast<int>(baseElevationGain * smoothScale);

                // Only add elevation if the scaled gain is meaningful.

                if (elevationGain > 0)
                {
                    auto desiredElevation = currentElevation + elevationGain;

                    // Limit elevation based on adjacent tiles to prevent steep slopes.

                    auto maxAllowedElevation = GetMaxAllowedElevation(x, y, currentElevation);

                    // Use the minimum of desired elevation and max allowed elevation.

                    auto newElevation = desiredElevation;

                    if (newElevation > maxAllowedElevation)
                    {
                        newElevation = maxAllowedElevation;
                    }

                    // Final safety clamp (elevation cap and minimum).

                    tile->SetElevation(ClampElevation(newElevation));
                }
            }
        }
    }
}