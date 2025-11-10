//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include <cmath>

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateElevationWithBiomes() const
    {
        // Create a more natural elevation system using overlapping hills and valleys
        // This creates a more organic terrain pattern

        auto numMajorHills{40 + GetRandomInt(20)};

        for (auto i = 0; i < numMajorHills; i++)
        {
            auto xCenter{GetRandomInt(m_size.width)};
            auto yCenter{GetRandomInt(m_size.height)};
            auto radius{CInt(8 * m_scale + GetRandomInt(12 * m_scale))};
            auto maxElevation{30 + GetRandomInt(20)};

            CreateElevationHill(xCenter, yCenter, radius, maxElevation);
        }
    }

    void WorldGenerator::GenerateMountainRanges() const
    {
        // Create mountain ranges - chains of connected hills
        auto numMountainRanges{3 + GetRandomInt(3)};

        for (auto range = 0; range < numMountainRanges; range++)
        {
            auto startX{GetRandomInt(m_size.width)};
            auto startY{GetRandomInt(m_size.height)};
            auto length{30 + GetRandomInt(40)};
            auto direction{GetRandomInt(360)};

            auto currentX = static_cast<float>(startX);
            auto currentY = static_cast<float>(startY);

            for (auto i = 0; i < length; i++)
            {
                auto x{CInt(currentX)};
                auto y{CInt(currentY)};

                if (m_worldArea->IsValidCoordinate(x, y))
                {
                    auto radius{CInt(4 * m_scale + GetRandomInt(6 * m_scale))};
                    auto elevation{120 + GetRandomInt(160)};

                    CreateElevationHill(x, y, radius, elevation);
                }

                // Move along the mountain range with some variation
                auto angleRad = (direction + GetRandomInt(60) - 30) * M_PI / 180.0f;
                currentX += std::cos(angleRad) * (2.0f + GetRandomInt(3));
                currentY += std::sin(angleRad) * (2.0f + GetRandomInt(3));

                // Occasionally change direction
                if (GetRandomInt(100) < 20)
                {
                    direction += GetRandomInt(60) - 30;
                    if (direction < 0)
                        direction += 360;
                    if (direction >= 360)
                        direction -= 360;
                }
            }
        }
    }

    void WorldGenerator::GenerateValleys() const
    {
        // Create valleys by reducing elevation in certain areas
        auto numValleys{15 + GetRandomInt(10)};

        for (auto i = 0; i < numValleys; i++)
        {
            auto xCenter{GetRandomInt(m_size.width)};
            auto yCenter{GetRandomInt(m_size.height)};
            auto radius{CInt(10 * m_scale + GetRandomInt(15 * m_scale))};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!m_worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto distance = GetDistance(x, y, xCenter, yCenter);
                    if (distance > radius)
                    {
                        continue;
                    }

                    auto tile = m_worldArea->GetTile(x, y);
                    if (!tile)
                    {
                        continue;
                    }

                    // Reduce elevation in valleys (but not below 0)
                    auto normalizedDistance = distance / radius;
                    auto elevationReduction = static_cast<int>((1.0f - normalizedDistance) * 40.0f);

                    auto currentElevation = tile->GetElevation();
                    auto newElevation = currentElevation - elevationReduction;
                    
                    // Clamp elevation to valid range (0 to max)
                    tile->SetElevation(ClampElevation(newElevation));
                }
            }
        }
    }

    void WorldGenerator::EnforceMinimumElevationForNonWaterTiles() const
    {
        // Enforce that all non-water tiles have elevation >= 1
        // Exception: tiles adjacent to water can have elevation < 1
        for (auto y = 0; y < m_size.height; y++)
        {
            for (auto x = 0; x < m_size.width; x++)
            {
                auto tile = m_worldArea->GetTile(x, y);
                if (!tile)
                {
                    continue;
                }

                // Skip water tiles
                if (tile->GetGround() == Hash("GroundWater"))
                {
                    continue;
                }

                // Check if elevation is below 1
                auto currentElevation = tile->GetElevation();
                if (currentElevation < 1)
                {
                    // Exception: if tile is adjacent to water, leave elevation as is
                    if (!IsAdjacentToWater(x, y))
                    {
                        // Set elevation to at least 1
                        tile->SetElevation(1);
                    }
                }
            }
        }
    }
}
