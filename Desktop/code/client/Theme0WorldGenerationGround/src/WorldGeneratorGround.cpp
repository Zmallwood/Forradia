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
    void WorldGeneratorGround::GenerateGroundWithElevation() const
    {
        ClearWithDirt();

        GenerateElevationWithBiomes();

        GenerateMountainRanges();

        GenerateValleys();

        GenerateGrassBiomes();

        GenerateRockFormations();
    }

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

            CreateBiomeCluster(xCenter, yCenter, radius, "GroundGrass");
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
                    tile->SetGround("GroundGrass");
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
                        rockTile->SetGround("GroundRock");
                    }
                }
            }
        }
    }
}