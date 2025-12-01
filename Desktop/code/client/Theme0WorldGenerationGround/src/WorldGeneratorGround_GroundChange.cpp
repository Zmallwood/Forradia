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
        void WorldGeneratorGround::GenerateGrassBiomes() const
        {
            // Obtain required data.

            auto worldArea{GetWorldArea()};

            auto worldAreaSize{GetWorldAreaSize()};

            auto worldScaling{GetWorldScaling()};

            // Create distinct grass biomes with organic shapes.
            // Grass appears in areas with moderate elevation (not mountains, not deep valleys).

            // Generate random number of grass biomes.

            auto numGrassBiomes{25 + GetRandomInt(15)};

            for (auto i = 0; i < numGrassBiomes; i++)
            {
                // Generate random center coordinates for the grass biome.

                auto xCenter{GetRandomInt(worldAreaSize.width)};

                auto yCenter{GetRandomInt(worldAreaSize.height)};

                // Check if this area is suitable for grass (moderate elevation, not water).

                auto tile{worldArea->GetTile(xCenter, yCenter)};

                if (!tile || tile->GetElevation() > 100 || tile->GetGround() == Hash("GroundWater"))
                {
                    continue;
                }

                // Generate random radius for the grass biome.

                auto radius{CInt(6 * worldScaling + GetRandomInt(10 * worldScaling))};

                // Generate random density for the grass biome.

                auto density{0.7f + GetRandomInt(30) / 100.0f}; // 0.7 to 1.0.

                // Create the grass biome.

                CreateBiomeCluster(xCenter, yCenter, radius, "GroundGrass");
            }

            // Also add grass in valleys and low-lying areas naturally.

            for (auto y = 0; y < worldAreaSize.height; y++)
            {
                for (auto x = 0; x < worldAreaSize.width; x++)
                {
                    // Get the tile.

                    auto tile = worldArea->GetTile(x, y);

                    // Skip if the tile is not found.

                    if (!tile)
                    {
                        continue;
                    }

                    // Grass naturally grows in low-lying areas that aren't water.

                    if (tile->GetElevation() <= 20 && tile->GetGround() != Hash("GroundWater") &&
                        tile->GetGround() != Hash("GroundRock"))
                    {
                        // Do the ground change.

                        tile->SetGround("GroundGrass");
                    }
                }
            }
        }

        void WorldGeneratorGround::GenerateRockFormations() const
        {
            // Obtain required data.

            auto worldArea{GetWorldArea()};

            auto worldAreaSize{GetWorldAreaSize()};

            auto worldScaling{GetWorldScaling()};

            // Place rocks on mountain peaks and high elevation areas.

            auto numRockFormations{20 + GetRandomInt(15)};

            // Create rock formations.

            for (auto i = 0; i < numRockFormations; i++)
            {
                // Generate random center coordinates for the rock formation.

                auto xCenter{GetRandomInt(worldAreaSize.width)};

                auto yCenter{GetRandomInt(worldAreaSize.height)};

                // Get the tile.

                auto tile{worldArea->GetTile(xCenter, yCenter)};

                // Skip if the tile is not found or the elevation is less than 80.

                if (!tile || tile->GetElevation() < 80)
                {
                    continue;
                }

                // Create rock formations on high elevation.

                // Generate random radius for the rock formation.

                auto radius{CInt(2 * worldScaling + GetRandomInt(5 * worldScaling))};

                // Create the rock formation.

                for (auto y = yCenter - radius; y <= yCenter + radius; y++)
                {
                    for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                    {
                        // Skip if the coordinates are out of bounds.

                        if (!worldArea->IsValidCoordinate(x, y))
                        {
                            continue;
                        }

                        // Calculate the distance from the center of the rock formation to the tile.

                        auto distance{GetDistance(x, y, xCenter, yCenter)};

                        // Skip if the distance is greater than the radius.

                        if (distance > radius)
                        {
                            continue;
                        }

                        // Get the tile.

                        auto rockTile{worldArea->GetTile(x, y)};

                        // Skip if the tile is not found or the ground is water.

                        if (!rockTile || rockTile->GetGround() == Hash("GroundWater"))
                        {
                            continue;
                        }

                        // Higher elevation = more likely to be rock.

                        auto elevation{rockTile->GetElevation()};

                        if (elevation > 60)
                        {
                            // Do the ground change.

                            rockTile->SetGround("GroundRock");
                        }
                    }
                }
            }
        }

        void WorldGeneratorGround::CreateBiomeCluster(int centerX, int centerY, int radius,
                                                      StringView groundType) const
        {
            // Enumerate all tiles in the radius.

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    // Skip if the tile is out of bounds.

                    if (!GetWorldArea()->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    // Calculate the distance between the tile and the center of the cluster.

                    auto distance{GetDistance(x, y, centerX, centerY)};

                    // Skip if the distance is greater than the radius.

                    if (distance > radius)
                    {
                        continue;
                    }

                    // Get the tile at the given coordinates.

                    auto tile{GetWorldArea()->GetTile(x, y)};

                    // Set the ground type of the tile.

                    if (tile)
                    {
                        tile->SetGround(groundType);
                    }
                }
            }
        }
    }
}