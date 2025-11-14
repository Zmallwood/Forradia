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
    void WorldGeneratorBase::CreateElevationHill(int centerX, int centerY, int radius,
                                                 int maxElevation) const
    {
        // Traverse the candidate tiles within the bounding square of the hill footprint.

        for (auto y = centerY - radius; y <= centerY + radius; y++)
        {
            for (auto x = centerX - radius; x <= centerX + radius; x++)
            {
                // Skip if the tile is out of bounds.

                if (!m_worldArea->IsValidCoordinate(x, y))
                {
                    continue;
                }

                // Calculate the distance from the center of the hill to the tile.

                auto distance{GetDistance(x, y, centerX, centerY)};

                // Skip if the tile is outside of the circular hill radius.

                if (distance > radius)
                {
                    continue;
                }

                // Get the tile.

                auto tile{m_worldArea->GetTile(x, y)};

                // Skip if the tile is not found.

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

                auto maxElevation{GetMaxElevation()};

                // Skip if already at maximum.

                if (currentElevation >= maxElevation)
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

                // Start reducing gain when we're above 60% of max elevation for a smoother
                // transition.

                auto elevationRatio{static_cast<float>(currentElevation) /
                                    static_cast<float>(maxElevation)};

                // Start falloff at 60 % of max elevation.

                auto falloffStart{0.6f};

                auto smoothScale{1.0f};

                if (elevationRatio >= falloffStart)
                {
                    // Smooth falloff using a smoothstep-like curve for very gradual transition.
                    // When at falloffStart (60%), scale is 1.0.
                    // When at 1.0 (100%), scale is 0.0.

                    auto falloffRange{1.0f - falloffStart};

                    // t goes from 0 to 1.

                    auto t{(elevationRatio - falloffStart) / falloffRange};

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