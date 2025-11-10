//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateBiomeBasedTerrain() const
    {
        // This method is called after elevation generation
        // It sets up the basic terrain based on elevation and biome regions
        // The actual grass placement is handled by GenerateGrassBiomes
    }

    void WorldGenerator::GenerateGrassBiomes() const
    {
        // Create distinct grass biomes with organic shapes
        // Grass appears in areas with moderate elevation (not mountains, not deep valleys)
        auto numGrassBiomes{25 + GetRandomInt(15)};

        for (auto i = 0; i < numGrassBiomes; i++)
        {
            auto xCenter{GetRandomInt(m_size.width)};
            auto yCenter{GetRandomInt(m_size.height)};

            // Check if this area is suitable for grass (moderate elevation, not water)
            auto tile = m_worldArea->GetTile(xCenter, yCenter);
            if (!tile || tile->GetElevation() > 100 || tile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            auto radius{CInt(6 * m_scale + GetRandomInt(10 * m_scale))};
            auto density{0.7f + GetRandomInt(30) / 100.0f}; // 0.7 to 1.0

            CreateBiomeCluster(xCenter, yCenter, radius, "GroundGrass", density);
        }

        // Also add grass in valleys and low-lying areas naturally
        for (auto y = 0; y < m_size.height; y++)
        {
            for (auto x = 0; x < m_size.width; x++)
            {
                auto tile = m_worldArea->GetTile(x, y);
                if (!tile)
                {
                    continue;
                }

                // Grass naturally grows in low-lying areas that aren't water
                if (tile->GetElevation() <= 20 && tile->GetGround() != Hash("GroundWater") &&
                    tile->GetGround() != Hash("GroundRock"))
                {
                    if (GetRandomInt(100) < 40)
                    {
                        tile->SetGround("GroundGrass");
                    }
                }
            }
        }
    }

    void WorldGenerator::GenerateRockFormations() const
    {
        // Place rocks on mountain peaks and high elevation areas
        auto numRockFormations{20 + GetRandomInt(15)};

        for (auto i = 0; i < numRockFormations; i++)
        {
            auto xCenter{GetRandomInt(m_size.width)};
            auto yCenter{GetRandomInt(m_size.height)};

            auto tile = m_worldArea->GetTile(xCenter, yCenter);
            if (!tile || tile->GetElevation() < 80)
            {
                continue;
            }

            // Create rock formations on high elevation
            auto radius{CInt(2 * m_scale + GetRandomInt(5 * m_scale))};

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

                    auto rockTile = m_worldArea->GetTile(x, y);
                    if (!rockTile || rockTile->GetGround() == Hash("GroundWater"))
                    {
                        continue;
                    }

                    // Higher elevation = more likely to be rock
                    auto elevation = rockTile->GetElevation();
                    if (elevation > 60)
                    {
                        auto rockProbability = (elevation - 60) * 5 / 4; // Scaled probability based on elevation
                        if (GetRandomInt(100) < rockProbability)
                        {
                            rockTile->SetGround("GroundRock");
                        }
                    }
                }
            }
        }
    }
}

