//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorGround.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorGround::GenerateElevationWithBiomes() const
    {
        auto size{GetSize()};

        auto scale{GetScale()};

        auto numMajorHills{40 + GetRandomInt(20)};

        for (auto i = 0; i < numMajorHills; i++)
        {
            auto xCenter{GetRandomInt(size.width)};

            auto yCenter{GetRandomInt(size.height)};

            auto radius{CInt(8 * scale + GetRandomInt(12 * scale))};

            auto maxElevation{30 + GetRandomInt(20)};

            CreateElevationHill(xCenter, yCenter, radius, maxElevation);
        }
    }

    void WorldGeneratorGround::GenerateMountainRanges() const
    {
        auto worldArea{GetWorldArea()};

        auto size{GetSize()};

        auto scale{GetScale()};

        // Create mountain ranges - chains of connected hills.

        auto numMountainRanges{3 + GetRandomInt(3)};

        for (auto range = 0; range < numMountainRanges; range++)
        {
            auto startX{GetRandomInt(size.width)};

            auto startY{GetRandomInt(size.height)};

            auto length{30 + GetRandomInt(40)};

            auto direction{GetRandomInt(360)};

            auto currentX = static_cast<float>(startX);

            auto currentY = static_cast<float>(startY);

            for (auto i = 0; i < length; i++)
            {
                auto x{CInt(currentX)};

                auto y{CInt(currentY)};

                if (worldArea->IsValidCoordinate(x, y))
                {
                    auto radius{CInt(4 * scale + GetRandomInt(6 * scale))};

                    auto elevation{120 + GetRandomInt(160)};

                    CreateElevationHill(x, y, radius, elevation);
                }

                // Move along the mountain range with some variation.

                auto angleRad = (direction + GetRandomInt(60) - 30) * M_PI / 180.0f;

                currentX += std::cos(angleRad) * (2.0f + GetRandomInt(3));

                currentY += std::sin(angleRad) * (2.0f + GetRandomInt(3));

                // Occasionally change direction.

                if (GetRandomInt(100) < 20)
                {
                    direction += GetRandomInt(60) - 30;

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

    void WorldGeneratorGround::GenerateValleys() const
    {
        auto worldArea{GetWorldArea()};

        auto size{GetSize()};

        auto scale{GetScale()};

        // Create valleys by reducing elevation in certain areas.

        auto numValleys{15 + GetRandomInt(10)};

        for (auto i = 0; i < numValleys; i++)
        {
            auto xCenter{GetRandomInt(size.width)};

            auto yCenter{GetRandomInt(size.height)};

            auto radius{CInt(10 * scale + GetRandomInt(15 * scale))};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto distance = GetDistance(x, y, xCenter, yCenter);

                    if (distance > radius)
                    {
                        continue;
                    }

                    auto tile = worldArea->GetTile(x, y);

                    if (!tile)
                    {
                        continue;
                    }

                    // Reduce elevation in valleys (but not below 0).

                    auto normalizedDistance = distance / radius;

                    auto elevationReduction = static_cast<int>((1.0f - normalizedDistance) * 40.0f);

                    auto currentElevation = tile->GetElevation();

                    auto newElevation = currentElevation - elevationReduction;

                    // Clamp elevation to valid range (0 to max).

                    tile->SetElevation(ClampElevation(newElevation));
                }
            }
        }
    }
}