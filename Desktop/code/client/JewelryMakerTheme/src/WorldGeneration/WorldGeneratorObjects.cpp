/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "WorldGeneratorObjects.hpp"
#include "WorldStructure/ObjectsStack.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorObjects::generateObjects() -> void
    {
        generateForests();
        generateMeadows();
        generateObjectsInBiomes();
    }

    auto WorldGeneratorObjects::generateForests() -> void
    {
        auto worldArea{getWorldArea()};
        auto size{worldArea->getSize()};
        auto worldScaling{getWorldScaling()};

        // Create dense forest clusters.
        auto numForests{40 + getRandomInt(10)};

        for (auto i = 0; i < numForests; i++)
        {
            auto centerX{getRandomInt(size.width)};
            auto centerY{getRandomInt(size.height)};

            auto tile{worldArea->getTile(centerX, centerY)};

            If(!tile || !isValidForFlora(centerX, centerY))
            {
                continue;
            }

            auto radius{static_cast<int>(
                8 * worldScaling +
                static_cast<float>(getRandomInt(static_cast<int>(12 * worldScaling))))};
            auto treeDensity{0.05F + static_cast<float>(getRandomInt(5)) / 100.0F};

            auto useFir{getRandomInt(100) < 60};

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    If(!worldArea->isValidCoordinate(x, y))
                    {
                        continue;
                    }

                    If(!isValidForFlora(x, y))
                    {
                        continue;
                    }

                    auto distance{calcDistance(x, y, centerX, centerY)};

                    If(distance > static_cast<float>(radius))
                    {
                        continue;
                    }

                    If(WorldGeneratorObjects::shouldAddForestObjects(treeDensity, distance, radius))
                    {
                        If(auto forestTile{worldArea->getTile(x, y)})
                        {
                            forestTile->getObjectsStack()->clearObjects();

                            WorldGeneratorObjects::addTreeToForestTile(forestTile, useFir);

                            WorldGeneratorObjects::addUndergrowthToForestTile(forestTile);
                        }
                    }
                }
            }
        }
    }

    auto WorldGeneratorObjects::shouldAddForestObjects(float treeDensity, float distance,
                                                       float radius) -> bool
    {
        auto normalizedDistance{distance / static_cast<float>(radius)};

        // Calculate the local density. Higher density in center, lower at edges.
        auto localDensity{treeDensity * (1.0F - normalizedDistance * 0.5F)};

        return getRandomInt(1000) < static_cast<int>(localDensity * 1000.0f);
    }

    auto WorldGeneratorObjects::addTreeToForestTile(const std::shared_ptr<Tile> &forestTile,
                                                    bool useFir) -> void
    { // Check if the forest should use fir or birch trees.
        If(useFir)
        {
            If(getRandomInt(100) < 70)
            {
                forestTile->getObjectsStack()->addObject("ObjectFirTree");
            }
            Else
            {
                forestTile->getObjectsStack()->addObject("ObjectBirchTree");
            }
        }
        Else
        {
            If(getRandomInt(100) < 70)
            {
                forestTile->getObjectsStack()->addObject("ObjectBirchTree");
            }
            Else
            {
                forestTile->getObjectsStack()->addObject("ObjectFirTree");
            }
        }
    }

    auto WorldGeneratorObjects::addUndergrowthToForestTile(const std::shared_ptr<Tile> &forestTile)
        -> void
    {
        // Add undergrowth in forests.
        If(getRandomInt(100) < 25)
        {
            If(getRandomInt(100) < 50)
            {
                forestTile->getObjectsStack()->addObject("ObjectBush1");
            }
            Else
            {
                forestTile->getObjectsStack()->addObject("ObjectBush2");
            }
        }
    }

    auto WorldGeneratorObjects::generateMeadows() -> void
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

            If(!tile || !isValidForFlora(centerX, centerY))
            {
                continue;
            }

            If(tile->getGround() != hash("GroundGrass"))
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
                    If(!worldArea->isValidCoordinate(x, y))
                    {
                        continue;
                    }

                    If(!isValidForFlora(x, y))
                    {
                        continue;
                    }

                    auto meadowTile{worldArea->getTile(x, y)};

                    If(!meadowTile || meadowTile->getGround() != hash("GroundGrass"))
                    {
                        continue;
                    }

                    auto distance{calcDistance(x, y, centerX, centerY)};

                    If(distance > static_cast<float>(radius))
                    {
                        continue;
                    }

                    // Add flowers.

                    If(getRandomInt(1000) < static_cast<int>(flowerDensity * 1000.0f))
                    {
                        meadowTile->getObjectsStack()->clearObjects();
                        meadowTile->getObjectsStack()->addObject("ObjectPinkFlower");
                    }
                    ElseIf(getRandomInt(1000) < static_cast<int>(grassDensity * 1000.0f))
                    {
                        meadowTile->getObjectsStack()->clearObjects();
                        meadowTile->getObjectsStack()->addObject("ObjectTallGrass");
                    }
                }
            }
        }
    }

    auto WorldGeneratorObjects::isValidForFlora(int x, int y) -> bool
    {
        If(!getWorldArea()->isValidCoordinate(x, y))
        {
            return false;
        }

        auto tile = getWorldArea()->getTile(x, y);

        If(!tile)
        {
            return false;
        }

        auto ground{tile->getGround()};

        return ground != hash("GroundWater") && ground != hash("GroundRock") &&
               tile->getWaterDepth() == 0;
    }
}
