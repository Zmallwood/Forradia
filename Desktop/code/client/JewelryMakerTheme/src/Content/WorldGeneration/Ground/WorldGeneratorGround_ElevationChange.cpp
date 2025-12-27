/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorGround.hpp"

#include "Content/WorldStructure/Tile.hpp"
#include "Content/WorldStructure/WorldArea.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorGround::generateElevationWithBiomes() const -> void
    {
        auto worldAreaSize{getWorldAreaSize()};
        auto worldScaling{getWorldScaling()};

        auto numMajorHills{40 + getRandomInt(20)};

        for (auto i = 0; i < numMajorHills; i++)
        {
            auto xCenter{getRandomInt(worldAreaSize.width)};
            auto yCenter{getRandomInt(worldAreaSize.height)};
            auto radius{static_cast<int>(
                8 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(12 * worldScaling))))};
            auto maxElevation{30 + getRandomInt(20)};

            createElevationHill(xCenter, yCenter, radius, maxElevation);
        }
    }

    auto WorldGeneratorGround::generateMountainRanges() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};
        auto worldScaling{getWorldScaling()};

        auto numMountainRanges{3 + getRandomInt(3)};

        for (auto range = 0; range < numMountainRanges; range++)
        {
            auto startX{getRandomInt(worldAreaSize.width)};
            auto startY{getRandomInt(worldAreaSize.height)};
            auto length{30 + getRandomInt(40)};
            auto direction{getRandomInt(360)};
            auto currentX{static_cast<float>(startX)};
            auto currentY{static_cast<float>(startY)};

            for (auto i = 0; i < length; i++)
            {
                auto x{static_cast<int>(currentX)};
                auto y{static_cast<int>(currentY)};

                if (worldArea->isValidCoordinate(x, y))
                {
                    auto radius{static_cast<int>(
                        4 * worldScaling +
                        static_cast<float>(getRandomInt(static_cast<int>(6 * worldScaling))))};

                    auto elevation{120 + getRandomInt(160)};

                    createElevationHill(x, y, radius, elevation);
                }

                // Move along the mountain range with some variation.
                auto angleRadians{
                    static_cast<float>((direction + getRandomInt(60) - 30) * M_PI / 180.0F)};

                currentX += std::cos(angleRadians) * (2.0f + static_cast<float>(getRandomInt(3)));
                currentY += std::sin(angleRadians) * (2.0f + static_cast<float>(getRandomInt(3)));

                // Occasionally change direction.
                if (getRandomInt(100) < 20)
                {
                    direction += getRandomInt(60) - 30;

                    if (direction < 0)
                    {
                        direction += 360;
                    }

                    if (direction >= 360)
                    {
                        direction -= 360;
                    }
                }
            }
        }
    }

    auto WorldGeneratorGround::generateValleys() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};
        auto worldScaling{getWorldScaling()};

        // Create valleys by reducing elevation in certain areas.
        auto numValleys{15 + getRandomInt(10)};

        for (auto i = 0; i < numValleys; i++)
        {
            auto xCenter{getRandomInt(worldAreaSize.width)};
            auto yCenter{getRandomInt(worldAreaSize.height)};
            auto radius{static_cast<int>(
                10 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(15 * worldScaling))))};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!worldArea->isValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto distance{getDistance(x, y, xCenter, yCenter)};

                    if (distance > static_cast<float>(radius))
                    {
                        continue;
                    }

                    auto tile = worldArea->getTile(x, y);

                    if (!tile)
                    {
                        continue;
                    }

                    auto normalizedDistance{distance / static_cast<float>(radius)};

                    // Calculate the elevation reduction based on the normalized distance.
                    auto elevationReduction{static_cast<int>((1.0F - normalizedDistance) * 40.0F)};

                    auto currentElevation{tile->getElevation()};
                    auto newElevation{currentElevation - elevationReduction};

                    // Clamp the new elevation to the valid range.
                    tile->setElevation(clampElevation(newElevation));
                }
            }
        }
    }

    auto WorldGeneratorGround::createElevationHill(int centerX, int centerY, int radius,
                                                   int maxElevation) const -> void
    {
        // Traverse the candidate tiles within the bounding square of the hill footprint.
        for (auto y = centerY - radius; y <= centerY + radius; y++)
        {
            for (auto x = centerX - radius; x <= centerX + radius; x++)
            {
                if (!getWorldArea()->isValidCoordinate(x, y))
                {
                    continue;
                }

                auto distance{getDistance(x, y, centerX, centerY)};

                if (distance > static_cast<float>(radius))
                {
                    continue;
                }

                auto tile{getWorldArea()->getTile(x, y)};

                if (!tile)
                {
                    continue;
                }

                if (tile->getGround() == hash("GroundWater"))
                {
                    continue;
                }

                auto currentElevation{tile->getElevation()};
                auto globalMaxElevation{getMaxElevation()};

                if (currentElevation >= globalMaxElevation)
                {
                    continue;
                }

                auto normalizedDistance{distance / static_cast<float>(radius)};

                auto baseElevationGain{
                    static_cast<float>((1.0F - normalizedDistance * normalizedDistance) *
                                       static_cast<float>(globalMaxElevation))};

                // Adjust the elevation gain to avoid abrupt height increases near the peak.

                // Apply smooth falloff as we approach the elevation cap.

                // Start reducing gain when we're above 60% of max elevation for a smoother
                // transition.

                auto elevationRatio{static_cast<float>(currentElevation) /
                                    static_cast<float>(globalMaxElevation)};

                // Start falloff at 60 % of max elevation.
                auto falloffStart{0.6F};

                auto smoothScale{1.0F};

                if (elevationRatio >= falloffStart)
                {
                    // Smooth falloff using a smoothstep-like curve for very gradual transition.
                    // When at falloffStart (60%), scale is 1.0.
                    // When at 1.0 (100%), scale is 0.0.

                    auto falloffRange{1.0F - falloffStart};

                    // t goes from 0 to 1.
                    auto t{(elevationRatio - falloffStart) / falloffRange};

                    // Use smoothstep curve: 3t^2 - 2t^3 for smooth S-curve transition.
                    // This gives a smoother, more natural falloff.

                    smoothScale = 1.0F - (t * t * (3.0F - 2.0F * t));
                }

                // Apply smooth scaling to elevation gain.
                auto elevationGain{static_cast<int>(baseElevationGain * smoothScale)};

                if (elevationGain > 0)
                {
                    // Calculate the target elevation before applying slope limits.
                    auto desiredElevation{currentElevation + elevationGain};

                    // Limit elevation based on adjacent tiles to prevent steep slopes.
                    auto maxAllowedElevation{getMaxAllowedElevation(x, y, currentElevation)};

                    // Use the minimum of desired elevation and max allowed elevation.
                    auto newElevation{desiredElevation};

                    if (newElevation > maxAllowedElevation)
                    {
                        // Respect the slope constraint when the desired elevation is too high.
                        newElevation = maxAllowedElevation;
                    }

                    // Final safety clamp (elevation cap and minimum).
                    tile->setElevation(clampElevation(newElevation));
                }
            }
        }
    }
}
