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
    void WorldGeneratorBase::SetAdjacentTilesElevationToZero(int x, int y) const
    {
        // Set elevation to 0 for all tiles adjacent to a water tile.
        // This creates a shoreline effect where land around water is at sea level.

        // Enumerate all eight surrounding directions for neighbor checks.

        // clang-format off

        int directions[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                             {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

        // clang-format on

        // Visit each neighboring tile and update elevation when needed.

        for (auto dir = 0; dir < 8; dir++)
        {
            // Compute the coordinates of the adjacent tile relative to the water tile.

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

            // Only set elevation to 0 for non-water tiles (shoreline).

            if (adjTile->GetGround() != Hash("GroundWater"))
            {
                adjTile->SetElevation(0);
            }
        }
    }

    void WorldGeneratorBase::CreateElevationHill(int centerX, int centerY, int radius,
                                                 int maxElevation) const
    {
        // Traverse the candidate tiles within the bounding square of the hill footprint.

        for (auto y = centerY - radius; y <= centerY + radius; y++)
        {
            for (auto x = centerX - radius; x <= centerX + radius; x++)
            {
                if (!m_worldArea->IsValidCoordinate(x, y))
                {
                    continue;
                }

                auto distance{GetDistance(x, y, centerX, centerY)};

                if (distance > radius)
                {
                    // Skip tiles outside of the circular hill radius.

                    continue;
                }

                auto tile{m_worldArea->GetTile(x, y)};

                if (!tile)
                {
                    continue;
                }

                // Skip water tiles.

                if (tile->GetGround() == Hash("GroundWater"))
                {
                    // Preserve water elevation to maintain coastlines.

                    continue;
                }

                // Check current elevation for smooth capping.

                auto currentElevation{tile->GetElevation()};

                auto maxElev{GetMaxElevation()};

                // Skip if already at maximum.

                if (currentElevation >= maxElev)
                {
                    // Prevent further elevation changes once the cap is reached.

                    continue;
                }

                // Create smooth elevation based on distance.

                auto normalizedDistance{distance / radius};

                auto baseElevationGain{static_cast<float>(
                    (1.0f - normalizedDistance * normalizedDistance) * maxElevation)};

                // Adjust the elevation gain to avoid abrupt height increases near the peak.

                // Apply smooth falloff as we approach the elevation cap.

                // Start reducing gain when we're above 60% of max elevation for a smoother transition.

                auto elevationRatio{static_cast<float>(currentElevation) /
                                    static_cast<float>(maxElev)};

                auto falloffStart{0.6f}; // Start falloff at 60 % of max elevation.

                auto smoothScale{1.0f};

                if (elevationRatio >= falloffStart)
                {
                    // Smooth falloff using a smoothstep-like curve for very gradual transition.
                    // When at falloffStart (60%), scale is 1.0.
                    // When at 1.0 (100%), scale is 0.0.

                    auto falloffRange{1.0f - falloffStart};

                    auto t{(elevationRatio - falloffStart) / falloffRange}; // t goes from 0 to 1.

                    // Use smoothstep curve: 3t^2 - 2t^3 for smooth S-curve transition.
                    // This gives a smoother, more natural falloff.

                    smoothScale = 1.0f - (t * t * (3.0f - 2.0f * t));
                }

                // Apply smooth scaling to elevation gain.

                auto elevationGain{static_cast<int>(baseElevationGain * smoothScale)};

                // Only add elevation if the scaled gain is meaningful.

                if (elevationGain > 0)
                {
                    // Calculate the target elevation before applying slope limits.

                    auto desiredElevation{currentElevation + elevationGain};

                    // Limit elevation based on adjacent tiles to prevent steep slopes.

                    auto maxAllowedElevation{GetMaxAllowedElevation(x, y, currentElevation)};

                    // Use the minimum of desired elevation and max allowed elevation.

                    auto newElevation{desiredElevation};

                    if (newElevation > maxAllowedElevation)
                    {
                        // Respect the slope constraint when the desired elevation is too high.

                        newElevation = maxAllowedElevation;
                    }

                    // Final safety clamp (elevation cap and minimum).

                    tile->SetElevation(ClampElevation(newElevation));
                }
            }
        }
    }
}