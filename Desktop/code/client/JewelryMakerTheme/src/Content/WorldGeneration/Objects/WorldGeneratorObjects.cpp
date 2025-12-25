/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "WorldGeneratorObjects.hpp"
    #include "Content/WorldStructure/ObjectsStack.hpp"
    #include "Content/WorldStructure/Tile.hpp"
    #include "Content/WorldStructure/WorldArea.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorObjects::generateObjects() const -> void
    {
        generateForests();
        generateMeadows();
        generateObjectsInBiomes();
    }

    auto WorldGeneratorObjects::generateForests() const -> void
    {
        auto worldArea{getWorldArea()};
        auto size{worldArea->getSize()};
        auto worldScaling{getWorldScaling()};

        // Create dense forest clusters.
        auto numForests{15 + getRandomInt(10)};

        for (auto i = 0; i < numForests; i++)
        {
            auto centerX{getRandomInt(size.width)};
            auto centerY{getRandomInt(size.height)};

            auto tile{worldArea->getTile(centerX, centerY)};

            if (!tile || !isValidForFlora(centerX, centerY))
            {
                continue;
            }

            auto radius{static_cast<int>(
                8 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(12 * worldScaling))))};
            auto treeDensity{0.1F + static_cast<float>(getRandomInt(20)) / 100.0F};

            auto useFir{getRandomInt(100) < 60};

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    if (!worldArea->isValidCoordinate(x, y))
                    {
                        continue;
                    }

                    if (!isValidForFlora(x, y))
                    {
                        continue;
                    }

                    auto distance{getDistance(x, y, centerX, centerY)};

                    if (distance > static_cast<float>(radius))
                    {
                        continue;
                    }

                    auto normalizedDistance{distance / static_cast<float>(radius)};

                    // Calculate the local density. Higher density in center, lower at edges.
                    auto localDensity{treeDensity * (1.0F - normalizedDistance * 0.5F)};

                    if (getRandomInt(1000) < static_cast<int>(localDensity * 1000.0f))
                    {
                        if (auto forestTile{worldArea->getTile(x, y)})
                        {
                            forestTile->getObjectsStack()->clearObjects();

                            // Check if the forest should use fir or birch trees.
                            if (useFir)
                            {
                                if (getRandomInt(100) < 70)
                                {
                                    forestTile->getObjectsStack()->addObject("ObjectFirTree");
                                }
                                else
                                {
                                    forestTile->getObjectsStack()->addObject("ObjectBirchTree");
                                }
                            }
                            else
                            {
                                if (getRandomInt(100) < 70)
                                {
                                    forestTile->getObjectsStack()->addObject("ObjectBirchTree");
                                }
                                else
                                {
                                    forestTile->getObjectsStack()->addObject("ObjectFirTree");
                                }
                            }

                            // Add undergrowth in forests.
                            if (getRandomInt(100) < 25)
                            {
                                if (getRandomInt(100) < 50)
                                {
                                    forestTile->getObjectsStack()->addObject("ObjectBush1");
                                }
                                else
                                {
                                    forestTile->getObjectsStack()->addObject("ObjectBush2");
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    auto WorldGeneratorObjects::generateMeadows() const -> void
    {
        auto worldArea{getWorldArea()};
        auto size{worldArea->getSize()};
        auto worldScaling{getWorldScaling()};

        // Create meadow areas with flowers and tall grass.
        auto numMeadows{20 + getRandomInt(15)};

        for (auto i = 0; i < numMeadows; i++)
        {
            auto centerX{getRandomInt(size.width)};
            auto centerY{getRandomInt(size.height)};

            auto tile{worldArea->getTile(centerX, centerY)};

            if (!tile || !isValidForFlora(centerX, centerY))
            {
                continue;
            }

            if (tile->getGround() != hash("GroundGrass"))
            {
                continue;
            }

            auto radius{static_cast<int>(
                5 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(8 * worldScaling))))};

            auto flowerDensity{0.15f + static_cast<float>(getRandomInt(15)) / 100.0f};

            auto grassDensity{0.2f + static_cast<float>(getRandomInt(20)) / 100.0f};

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    if (!worldArea->isValidCoordinate(x, y))
                    {
                        continue;
                    }

                    if (!isValidForFlora(x, y))
                    {
                        continue;
                    }

                    auto meadowTile{worldArea->getTile(x, y)};

                    if (!meadowTile || meadowTile->getGround() != hash("GroundGrass"))
                    {
                        continue;
                    }

                    auto distance{getDistance(x, y, centerX, centerY)};

                    if (distance > static_cast<float>(radius))
                    {
                        continue;
                    }

                    // Add flowers.

                    if (getRandomInt(1000) < static_cast<int>(flowerDensity * 1000.0f))
                    {
                        meadowTile->getObjectsStack()->clearObjects();
                        meadowTile->getObjectsStack()->addObject("ObjectPinkFlower");
                    }
                    else if (getRandomInt(1000) < static_cast<int>(grassDensity * 1000.0f))
                    {
                        meadowTile->getObjectsStack()->clearObjects();
                        meadowTile->getObjectsStack()->addObject("ObjectTallGrass");
                    }
                }
            }
        }
    }

    auto WorldGeneratorObjects::isValidForFlora(int x, int y) const -> bool
    {
        if (!getWorldArea()->isValidCoordinate(x, y))
        {
            return false;
        }

        auto tile = getWorldArea()->getTile(x, y);

        if (!tile)
        {
            return false;
        }

        auto ground{tile->getGround()};

        return ground != hash("GroundWater") && ground != hash("GroundRock") &&
               tile->getWaterDepth() == 0;
    }
}
