//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorGround.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace AAK
{
    namespace Forradia::Theme0
    {
        void WorldGeneratorGround::GenerateElevationWithBiomes() const
        {
            // Obtain required data.

            auto worldAreaSize{GetWorldAreaSize()};

            auto worldScaling{GetWorldScaling()};

            // Create major hills.

            auto numMajorHills{40 + GetRandomInt(20)};

            for (auto i = 0; i < numMajorHills; i++)
            {
                // Generate random center coordinates for the hill.

                auto xCenter{GetRandomInt(worldAreaSize.width)};

                auto yCenter{GetRandomInt(worldAreaSize.height)};

                // Generate random radius for the hill.

                auto radius{CInt(8 * worldScaling + GetRandomInt(12 * worldScaling))};

                // Generate random maximum elevation for the hill.

                auto maxElevation{30 + GetRandomInt(20)};

                // Create the hill.

                CreateElevationHill(xCenter, yCenter, radius, maxElevation);
            }
        }

        void WorldGeneratorGround::GenerateMountainRanges() const
        {
            // Obtain required data.

            auto worldArea{GetWorldArea()};

            auto worldAreaSize{GetWorldAreaSize()};

            auto worldScaling{GetWorldScaling()};

            // Create mountain ranges - chains of connected hills.

            auto numMountainRanges{3 + GetRandomInt(3)};

            for (auto range = 0; range < numMountainRanges; range++)
            {
                // Generate random start coordinates for the mountain range.

                auto startX{GetRandomInt(worldAreaSize.width)};

                auto startY{GetRandomInt(worldAreaSize.height)};

                // Generate random length for the mountain range.

                auto length{30 + GetRandomInt(40)};

                // Generate random direction for the mountain range.

                auto direction{GetRandomInt(360)};

                // Initialize current coordinates for the mountain range.

                auto currentX{static_cast<float>(startX)};

                auto currentY{static_cast<float>(startY)};

                // Create the mountain range.

                for (auto i = 0; i < length; i++)
                {
                    // Get the current coordinates.

                    auto x{CInt(currentX)};

                    auto y{CInt(currentY)};

                    // If the coordinates are valid, create a hill.

                    if (worldArea->IsValidCoordinate(x, y))
                    {
                        // Generate random radius for the hill.

                        auto radius{CInt(4 * worldScaling + GetRandomInt(6 * worldScaling))};

                        // Generate random elevation for the hill.

                        auto elevation{120 + GetRandomInt(160)};

                        // Create the hill.

                        CreateElevationHill(x, y, radius, elevation);
                    }

                    // Move along the mountain range with some variation.

                    auto angleRadians{
                        static_cast<float>((direction + GetRandomInt(60) - 30) * M_PI / 180.0f)};

                    // Calculate the new coordinates based on the angle and distance.

                    currentX += std::cos(angleRadians) * (2.0f + GetRandomInt(3));

                    currentY += std::sin(angleRadians) * (2.0f + GetRandomInt(3));

                    // Occasionally change direction.

                    if (GetRandomInt(100) < 20)
                    {
                        // Change the direction of the mountain range.

                        direction += GetRandomInt(60) - 30;

                        // Make sure the direction is above 0.

                        if (direction < 0)
                        {
                            direction += 360;
                        }

                        // Make sure the direction is below 360.

                        if (direction >= 360)
                        {
                            direction -= 360;
                        }
                    }
                }
            }
        }

        void WorldGeneratorGround::GenerateValleys() const
        {
            // Obtain required data.

            auto worldArea{GetWorldArea()};

            auto worldAreaSize{GetWorldAreaSize()};

            auto worldScaling{GetWorldScaling()};

            // Create valleys by reducing elevation in certain areas.

            auto numValleys{15 + GetRandomInt(10)};

            for (auto i = 0; i < numValleys; i++)
            {
                // Generate random center coordinates for the valley.

                auto xCenter{GetRandomInt(worldAreaSize.width)};

                auto yCenter{GetRandomInt(worldAreaSize.height)};

                // Generate random radius for the valley.

                auto radius{CInt(10 * worldScaling + GetRandomInt(15 * worldScaling))};

                // Create the valley.

                for (auto y = yCenter - radius; y <= yCenter + radius; y++)
                {
                    for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                    {
                        // Skip if the coordinates are out of bounds.

                        if (!worldArea->IsValidCoordinate(x, y))
                        {
                            continue;
                        }

                        // Calculate the distance from the center of the valley to the tile.

                        auto distance{GetDistance(x, y, xCenter, yCenter)};

                        // Skip if the distance is greater than the radius.

                        if (distance > radius)
                        {
                            continue;
                        }

                        // Get the tile.

                        auto tile = worldArea->GetTile(x, y);

                        // Skip if the tile is not found.

                        if (!tile)
                        {
                            continue;
                        }

                        // Calculate the normalized distance from the center of the valley to the
                        // tile.

                        auto normalizedDistance{distance / radius};

                        // Calculate the elevation reduction based on the normalized distance.

                        auto elevationReduction{
                            static_cast<int>((1.0f - normalizedDistance) * 40.0f)};

                        // Get the current elevation of the tile.

                        auto currentElevation{tile->GetElevation()};

                        // Calculate the new elevation of the tile.

                        auto newElevation{currentElevation - elevationReduction};

                        // Clamp the new elevation to the valid range.

                        tile->SetElevation(ClampElevation(newElevation));
                    }
                }
            }
        }

        void WorldGeneratorGround::CreateElevationHill(int centerX, int centerY, int radius,
                                                       int maxElevation) const
        {
            // Traverse the candidate tiles within the bounding square of the hill footprint.

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    // Skip if the tile is out of bounds.

                    if (!GetWorldArea()->IsValidCoordinate(x, y))
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

                    auto tile{GetWorldArea()->GetTile(x, y)};

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
}