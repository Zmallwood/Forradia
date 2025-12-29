/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorGround.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorGround::generateGrassBiomes() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};
        auto worldScaling{getWorldScaling()};

        // Create distinct grass biomes with organic shapes.
        // Grass appears in areas with moderate elevation (not mountains, not deep valleys).

        // NOLINTNEXTLINE(readability-magic-numbers)
        auto numGrassBiomes{25 + getRandomInt(15)};

        for (auto i = 0; i < numGrassBiomes; i++)
        {
            auto xCenter{getRandomInt(worldAreaSize.width)};
            auto yCenter{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(xCenter, yCenter)};

            // Check if this area is suitable for grass (moderate elevation, not water).
            // NOLINTNEXTLINE(readability-magic-numbers)
            if (!tile || tile->getElevation() > 100 || tile->getGround() == hash("GroundWater"))
            {
                continue;
            }

            // NOLINTBEGIN(readability-magic-numbers)
            auto radius{static_cast<int>(
                6 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(10 * worldScaling))))};
            // NOLINTEND(readability-magic-numbers)

            createBiomeCluster(xCenter, yCenter, radius, "GroundGrass");
        }

        // Also add grass in valleys and low-lying areas naturally.

        for (auto yPos = 0; yPos < worldAreaSize.height; yPos++)
        {
            for (auto xPos = 0; xPos < worldAreaSize.width; xPos++)
            {
                auto tile = worldArea->getTile(xPos, yPos);

                if (!tile)
                {
                    continue;
                }

                // Grass naturally grows in low-lying areas that aren't water.
                // NOLINTBEGIN(readability-magic-numbers)
                if (tile->getElevation() <= 20 && tile->getGround() != hash("GroundWater") &&
                    tile->getGround() != hash("GroundRock"))
                {
                    tile->setGround("GroundGrass");
                }
                // NOLINTEND(readability-magic-numbers)
            }
        }
    }

    auto WorldGeneratorGround::generateRockFormations() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};
        auto worldScaling{getWorldScaling()};

        // NOLINTNEXTLINE(readability-magic-numbers)
        auto numRockFormations{20 + getRandomInt(15)};

        for (auto i = 0; i < numRockFormations; i++)
        {
            auto xCenter{getRandomInt(worldAreaSize.width)};
            auto yCenter{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(xCenter, yCenter)};

            // NOLINTNEXTLINE(readability-magic-numbers)
            if (!tile || tile->getElevation() < 80)
            {
                continue;
            }

            // Create rock formations on high elevation.

            // NOLINTBEGIN(readability-magic-numbers)
            auto radius{static_cast<int>(
                2 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(5 * worldScaling))))};
            // NOLINTEND(readability-magic-numbers)

            for (auto yPos = yCenter - radius; yPos <= yCenter + radius; yPos++)
            {
                for (auto xPos = xCenter - radius; xPos <= xCenter + radius; xPos++)
                {
                    if (!worldArea->isValidCoordinate(xPos, yPos))
                    {
                        continue;
                    }

                    auto distance{calcDistance(xPos, yPos, xCenter, yCenter)};

                    if (distance > static_cast<float>(radius))
                    {
                        continue;
                    }

                    auto rockTile{worldArea->getTile(xPos, yPos)};

                    if (WorldGeneratorGround::setTileGroundToRock(rockTile, xPos, yPos) == false)
                    {
                        continue;
                    }
                }
            }
        }
    }

    auto WorldGeneratorGround::setTileGroundToRock(const std::shared_ptr<Tile> &tile, int xPos,
                                                   int yPos) -> bool
    {
        // Skip if the tile is not found or the ground is water.

        if (!tile || tile->getGround() == hash("GroundWater"))
        {
            return false;
        }

        // Place rocks on mountain peaks and high elevation areas. Higher elevation =
        // more likely to be rock.

        auto elevation{tile->getElevation()};

        // NOLINTNEXTLINE(readability-magic-numbers)
        if (elevation > 60)
        {
            tile->setGround("GroundRock");
        }

        return true;
    }

    auto WorldGeneratorGround::createBiomeCluster(int centerX, int centerY, int radius,
                                                  std::string_view groundType) const -> void
    {
        // Enumerate all tiles in the radius.
        for (auto yPos = centerY - radius; yPos <= centerY + radius; yPos++)
        {
            for (auto xPos = centerX - radius; xPos <= centerX + radius; xPos++)
            {
                if (!getWorldArea()->isValidCoordinate(xPos, yPos))
                {
                    continue;
                }

                auto distance{calcDistance(xPos, yPos, centerX, centerY)};

                if (distance > static_cast<float>(radius))
                {
                    continue;
                }

                if (auto tile{getWorldArea()->getTile(xPos, yPos)})
                {
                    tile->setGround(groundType);
                }
            }
        }
    }
}
