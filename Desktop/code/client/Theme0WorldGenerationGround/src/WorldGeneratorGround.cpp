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
    void WorldGeneratorGround::ClearWithDirt() const
    {
        auto worldArea{GetWorldArea()};

        auto size{GetSize()};

        for (auto y = 0; y < size.height; y++)
        {
            for (auto x = 0; x < size.width; x++)
            {
                auto tile{worldArea->GetTile(x, y)};

                if (tile)
                {
                    tile->SetGround("GroundDirt");

                    tile->SetElevation(GetDefaultGroundElevation());
                }
            }
        }
    }

    void WorldGeneratorGround::GenerateBiomeBasedTerrain() const
    {
        // This method is called after elevation generation.
        // It sets up the basic terrain based on elevation and biome regions.
        // The actual grass placement is handled by GenerateGrassBiomes.
    }

    void WorldGeneratorGround::GenerateGrassBiomes() const
    {
        auto worldArea{GetWorldArea()};

        auto size{GetSize()};

        auto scale{GetScale()};

        // Create distinct grass biomes with organic shapes.
        // Grass appears in areas with moderate elevation (not mountains, not deep valleys).

        auto numGrassBiomes{25 + GetRandomInt(15)};

        for (auto i = 0; i < numGrassBiomes; i++)
        {
            auto xCenter{GetRandomInt(size.width)};

            auto yCenter{GetRandomInt(size.height)};

            // Check if this area is suitable for grass (moderate elevation, not water).

            auto tile = worldArea->GetTile(xCenter, yCenter);

            if (!tile || tile->GetElevation() > 100 || tile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            auto radius{CInt(6 * scale + GetRandomInt(10 * scale))};

            auto density{0.7f + GetRandomInt(30) / 100.0f}; // 0.7 to 1.0.

            CreateBiomeCluster(xCenter, yCenter, radius, "GroundGrass", density);
        }

        // Also add grass in valleys and low-lying areas naturally.

        for (auto y = 0; y < size.height; y++)
        {
            for (auto x = 0; x < size.width; x++)
            {
                auto tile = worldArea->GetTile(x, y);

                if (!tile)
                {
                    continue;
                }

                // Grass naturally grows in low-lying areas that aren't water.

                if (tile->GetElevation() <= 20 && tile->GetGround() != Hash("GroundWater") &&
                    tile->GetGround() != Hash("GroundRock"))
                {
                    if (GetRandomInt(100) < 40)
                    {
                        tile->SetGround("GroundGrass");

                        if (tile->GetElevation() < GetDefaultGroundElevation())
                        {
                            tile->SetElevation(GetDefaultGroundElevation());
                        }
                    }
                }
            }
        }
    }

    void WorldGeneratorGround::GenerateRockFormations() const
    {
        auto worldArea{GetWorldArea()};

        auto size{GetSize()};

        auto scale{GetScale()};

        // Place rocks on mountain peaks and high elevation areas.

        auto numRockFormations{20 + GetRandomInt(15)};

        for (auto i = 0; i < numRockFormations; i++)
        {
            auto xCenter{GetRandomInt(size.width)};

            auto yCenter{GetRandomInt(size.height)};

            auto tile = worldArea->GetTile(xCenter, yCenter);

            if (!tile || tile->GetElevation() < 80)
            {
                continue;
            }

            // Create rock formations on high elevation.

            auto radius{CInt(2 * scale + GetRandomInt(5 * scale))};

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

                    auto rockTile = worldArea->GetTile(x, y);

                    if (!rockTile || rockTile->GetGround() == Hash("GroundWater"))
                    {
                        continue;
                    }

                    // Higher elevation = more likely to be rock.

                    auto elevation = rockTile->GetElevation();

                    if (elevation > 60)
                    {
                        auto rockProbability =
                            (elevation - 60) * 5 / 4; // Scaled probability based on elevation.

                        if (GetRandomInt(100) < rockProbability)
                        {
                            rockTile->SetGround("GroundRock");

                            if (tile->GetElevation() < GetDefaultGroundElevation())
                            {
                                tile->SetElevation(GetDefaultGroundElevation());
                            }
                        }
                    }
                }
            }
        }
    }

    void WorldGeneratorGround::GenerateElevationWithBiomes() const
    {
        auto size{GetSize()};

        auto scale{GetScale()};

        // Create a more natural elevation system using overlapping hills and valleys.
        // This creates a more organic terrain pattern.

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