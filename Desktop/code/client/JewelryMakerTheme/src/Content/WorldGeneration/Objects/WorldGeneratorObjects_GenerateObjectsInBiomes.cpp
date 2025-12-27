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
    auto WorldGeneratorObjects::generateObjectsInBiomes() const -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{worldArea->getSize()};
        auto worldScaling{getWorldScaling()};

        // Add scattered objects throughout the world based on biomes.
        // This complements the forests and meadows.

        // Scattered trees outside of forests.

        auto numScatteredTrees{static_cast<int>(
            300 * worldScaling +
            static_cast<float>(getRandomInt(static_cast<int>(150 * worldScaling))))};

        for (auto i = 0; i < numScatteredTrees; i++)
        {
            auto x{getRandomInt(worldAreaSize.width)};
            auto y{getRandomInt(worldAreaSize.height)};

            auto tile = worldArea->getTile(x, y);

            if (!tile || !isValidForFlora(x, y))
            {
                continue;
            }

            // Check if the tile has grass ground and if the random number is less than 8.
            if (tile->getGround() == hash("GroundGrass") && getRandomInt(100) < 8)
            {
                tile->getObjectsStack()->clearObjects();

                // Add a tree with type of either fir or birch with a 50% chance.

                if (getRandomInt(100) < 50)
                {
                    tile->getObjectsStack()->addObject("ObjectFirTree");
                }
                else
                {
                    tile->getObjectsStack()->addObject("ObjectBirchTree");
                }
            }
        }

        // Scattered bushes.
        auto numScatteredBushes{static_cast<int>(
            1000 * worldScaling +
            static_cast<float>(getRandomInt(static_cast<int>(100 * worldScaling))))};

        for (auto i = 0; i < numScatteredBushes; i++)
        {
            auto x{getRandomInt(worldAreaSize.width)};
            auto y{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(x, y)};

            if (!tile || !isValidForFlora(x, y))
            {
                continue;
            }

            if (getRandomInt(100) < 8)
            {
                tile->getObjectsStack()->clearObjects();

                // Add a bush with type of either bush1 or bush2 with a 50% chance.
                if (getRandomInt(100) < 50)
                {
                    tile->getObjectsStack()->addObject("ObjectBush1");
                }
                else
                {
                    tile->getObjectsStack()->addObject("ObjectBush2");
                }
            }
        }

        // Stone boulders - prefer higher elevation areas.
        auto numBoulders{static_cast<int>(
            150 * worldScaling +
            static_cast<float>(getRandomInt(static_cast<int>(100 * worldScaling))))};

        for (auto i = 0; i < numBoulders; i++)
        {
            auto x{getRandomInt(worldAreaSize.width)};
            auto y{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(x, y)};

            if (!tile || tile->getWaterDepth() >= 4)
            {
                continue;
            }

            // Make it so that the tile has no other objects on it.
            tile->getObjectsStack()->clearObjects();

            // Add a stone boulder to the tile.
            tile->getObjectsStack()->addObject("ObjectStoneBoulder");
        }

        // Brown mushrooms - prefer forest areas with trees nearby.
        // Mushrooms grow on forest floors, often near trees.
        auto numMushrooms{static_cast<int>(
            600 * worldScaling +
            static_cast<float>(getRandomInt(static_cast<int>(400 * worldScaling))))};

        for (auto i = 0; i < numMushrooms; i++)
        {
            auto x{getRandomInt(worldAreaSize.width)};
            auto y{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(x, y)};

            if (!tile || !isValidForFlora(x, y))
            {
                continue;
            }

            auto ground{tile->getGround()};

            // Mushrooms prefer grass or dirt ground.
            if (ground != hash("GroundGrass") && ground != hash("GroundDirt"))
            {
                continue;
            }

            // Don't place mushrooms on tiles that already have trees or large objects.
            // (mushrooms are undergrowth, not replacement for trees).

            auto objectsStack{tile->getObjectsStack()};

            if (objectsStack->getSize() > 0)
            {
                continue;
            }

            // Check if there are objects (likely trees) nearby.
            // Mushrooms often grow near trees in forest environments.

            auto nearbyObjectsCount{0};

            for (auto checkY = y - 2; checkY <= y + 2; checkY++)
            {
                for (auto checkX = x - 2; checkX <= x + 2; checkX++)
                {
                    if (checkX == x && checkY == y)
                    {
                        continue;
                    }

                    if (!worldArea->isValidCoordinate(checkX, checkY))
                    {
                        continue;
                    }

                    auto nearbyTile{worldArea->getTile(checkX, checkY)};

                    if (nearbyTile && nearbyTile->getObjectsStack()->getSize() > 0)
                    {
                        nearbyObjectsCount++;
                    }
                }
            }

            // Higher probability if there are objects (trees) nearby (forest environment).
            // Mushrooms thrive in forest ecosystems.

            auto baseProbability{6};

            // +3% per nearby object (tree).

            auto forestBonus{nearbyObjectsCount * 3};

            auto mushroomProbability{baseProbability + forestBonus};

            if (mushroomProbability > 25)
            {
                mushroomProbability = 25;
            }

            if (getRandomInt(100) < mushroomProbability)
            {
                tile->getObjectsStack()->clearObjects();
                tile->getObjectsStack()->addObject("ObjectBrownMushroom");
            }
        }

        auto numStones{static_cast<int>(
            1000 * worldScaling +
            static_cast<float>(getRandomInt(static_cast<int>(100 * worldScaling))))};

        for (auto i = 0; i < numStones; i++)
        {
            auto x{getRandomInt(worldAreaSize.width)};
            auto y{getRandomInt(worldAreaSize.height)};

            auto tile{worldArea->getTile(x, y)};

            if (!tile || tile->getGround() == hash("GroundWater") || tile->getWaterDepth() > 0)
            {
                continue;
            }

            auto objectsStack{tile->getObjectsStack()};

            if (objectsStack->getSize() > 0)
            {
                continue;
            }

            objectsStack->clearObjects();
            objectsStack->addObject("ObjectStone");
        }
    }
}
