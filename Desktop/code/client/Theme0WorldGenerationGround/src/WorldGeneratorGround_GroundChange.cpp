/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Tile.hpp"
#include "WorldArea.hpp"
#include "WorldGeneratorGround.hpp"

namespace Forradia::Theme0
{
    auto WorldGeneratorGround::generateGrassBiomes() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};
        auto worldScaling{getWorldScaling()};

        // Create distinct grass biomes with organic shapes.
        // Grass appears in areas with moderate elevation (not mountains, not deep valleys).

        auto numGrassBiomes{25 + getRandomInt(15)};

        for (auto i = 0; i < numGrassBiomes; i++)
        {
            auto xCenter{getRandomInt(worldAreaSize.width)};
            auto yCenter{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(xCenter, yCenter)};

            // Check if this area is suitable for grass (moderate elevation, not water).
            if (!tile || tile->getElevation() > 100 || tile->getGround() == hash("GroundWater"))
            {
                continue;
            }

            auto radius{static_cast<int>(
                6 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(10 * worldScaling))))};
            //
            createBiomeCluster(xCenter, yCenter, radius, "GroundGrass");
        }

        // Also add grass in valleys and low-lying areas naturally.

        for (auto y = 0; y < worldAreaSize.height; y++)
        {
            for (auto x = 0; x < worldAreaSize.width; x++)
            {
                auto tile = worldArea->getTile(x, y);

                if (!tile)
                {
                    continue;
                }

                // Grass naturally grows in low-lying areas that aren't water.
                if (tile->getElevation() <= 20 && tile->getGround() != hash("GroundWater") &&
                    tile->getGround() != hash("GroundRock"))
                {
                    tile->setGround("GroundGrass");
                }
            }
        }
    }

    auto WorldGeneratorGround::generateRockFormations() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};
        auto worldScaling{getWorldScaling()};

        auto numRockFormations{20 + getRandomInt(15)};

        for (auto i = 0; i < numRockFormations; i++)
        {
            auto xCenter{getRandomInt(worldAreaSize.width)};
            auto yCenter{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(xCenter, yCenter)};

            if (!tile || tile->getElevation() < 80)
            {
                continue;
            }

            // Create rock formations on high elevation.

            auto radius{static_cast<int>(
                2 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(5 * worldScaling))))};

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

                    auto rockTile{worldArea->getTile(x, y)};

                    // Skip if the tile is not found or the ground is water.

                    if (!rockTile || rockTile->getGround() == hash("GroundWater"))
                    {
                        continue;
                    }

                    // Place rocks on mountain peaks and high elevation areas. Higher elevation =
                    // more likely to be rock.

                    auto elevation{rockTile->getElevation()};

                    if (elevation > 60)
                    {
                        rockTile->setGround("GroundRock");
                    }
                }
            }
        }
    }

    auto WorldGeneratorGround::createBiomeCluster(int centerX, int centerY, int radius,
                                                  std::string_view groundType) const -> void
    {
        // Enumerate all tiles in the radius.
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

                if (auto tile{getWorldArea()->getTile(x, y)})
                {
                    tile->setGround(groundType);
                }
            }
        }
    }
}
