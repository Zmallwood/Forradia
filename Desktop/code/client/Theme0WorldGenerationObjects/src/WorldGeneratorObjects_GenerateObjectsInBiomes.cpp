//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "ObjectsStack.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"
#include "WorldGeneratorObjects.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorObjects::GenerateObjectsInBiomes() const
    {
        // Obtain required data.

        auto worldArea{GetWorldArea()};

        auto worldAreaSize{worldArea->GetSize()};

        auto worldScaling{GetWorldScaling()};

        // Add scattered objects throughout the world based on biomes.
        // This complements the forests and meadows.

        // Scattered trees outside of forests.

        // Number of scattered trees.

        auto numScatteredTrees{300 * worldScaling + GetRandomInt(150 * worldScaling)};

        // Create the scattered trees.

        for (auto i = 0; i < numScatteredTrees; i++)
        {
            // Obtain a random position for the tree.

            auto x{GetRandomInt(worldAreaSize.width)};

            auto y{GetRandomInt(worldAreaSize.height)};

            // Obtain the tile at the random position.

            auto tile = worldArea->GetTile(x, y);

            // Do not continue if the tile is invalid or not valid for a tree.

            if (!tile || !IsValidForFlora(x, y))
            {
                continue;
            }

            // Prefer grass ground for scattered trees.

            // Check if the tile has grass ground and if the random number is less than 8.

            if (tile->GetGround() == Hash("GroundGrass") && GetRandomInt(100) < 8)
            {
                // Clear the objects stack on the tile.

                tile->GetObjectsStack()->ClearObjects();

                // Add a tree with type of either fir or birch with a 50% chance.

                if (GetRandomInt(100) < 50)
                {
                    tile->GetObjectsStack()->AddObject("ObjectFirTree");
                }
                else
                {
                    tile->GetObjectsStack()->AddObject("ObjectBirchTree");
                }
            }
        }

        // Scattered bushes.

        // Number of scattered bushes.

        auto numScatteredBushes{1000 * worldScaling + GetRandomInt(100 * worldScaling)};

        // Create the scattered bushes.

        for (auto i = 0; i < numScatteredBushes; i++)
        {
            // Obtain a random position for the bush.

            auto x{GetRandomInt(worldAreaSize.width)};

            auto y{GetRandomInt(worldAreaSize.height)};

            // Obtain the tile at the random position.

            auto tile{worldArea->GetTile(x, y)};

            // Do not continue if the tile is invalid or not valid for a bush.

            if (!tile || !IsValidForFlora(x, y))
            {
                continue;
            }

            // Check probability of adding a bush.

            if (GetRandomInt(100) < 8)
            {
                // Make it so that the tile has no other objects on it.

                tile->GetObjectsStack()->ClearObjects();

                // Add a bush with type of either bush1 or bush2 with a 50% chance.

                if (GetRandomInt(100) < 50)
                {
                    tile->GetObjectsStack()->AddObject("ObjectBush1");
                }
                else
                {
                    tile->GetObjectsStack()->AddObject("ObjectBush2");
                }
            }
        }

        // Stone boulders - prefer higher elevation areas.

        // Number of stone boulders.

        auto numBoulders{150 * worldScaling + GetRandomInt(100 * worldScaling)};

        // Create the stone boulders.

        for (auto i = 0; i < numBoulders; i++)
        {
            // Obtain a random position for the boulder.

            auto x{GetRandomInt(worldAreaSize.width)};

            auto y{GetRandomInt(worldAreaSize.height)};

            // Obtain the tile at the random position.

            auto tile{worldArea->GetTile(x, y)};

            // Do not continue if the tile is invalid or the water depth is greater than or
            // equal to 4.

            if (!tile || tile->GetWaterDepth() >= 4)
            {
                continue;
            }

            // Higher elevation = more likely to have boulders.

            auto elevation{tile->GetElevation()};

            // Make it so that the tile has no other objects on it.

            tile->GetObjectsStack()->ClearObjects();

            // Add a stone boulder to the tile.

            tile->GetObjectsStack()->AddObject("ObjectStoneBoulder");
        }

        // Brown mushrooms - prefer forest areas with trees nearby.
        // Mushrooms grow on forest floors, often near trees.

        // Number of brown mushrooms.

        auto numMushrooms{600 * worldScaling + GetRandomInt(400 * worldScaling)};

        // Create the brown mushrooms.

        for (auto i = 0; i < numMushrooms; i++)
        {
            // Obtain a random position for the mushroom.

            auto x{GetRandomInt(worldAreaSize.width)};

            auto y{GetRandomInt(worldAreaSize.height)};

            // Obtain the tile at the random position.

            auto tile{worldArea->GetTile(x, y)};

            // Do not continue if the tile is invalid or not valid for a mushroom.

            if (!tile || !IsValidForFlora(x, y))
            {
                continue;
            }

            // Mushrooms prefer grass or dirt ground.

            auto ground{tile->GetGround()};

            if (ground != Hash("GroundGrass") && ground != Hash("GroundDirt"))
            {
                continue;
            }

            // Don't place mushrooms on tiles that already have trees or large objects.
            // (mushrooms are undergrowth, not replacement for trees).

            auto objectsStack{tile->GetObjectsStack()};

            if (objectsStack->GetSize() > 0)
            {
                // Skip if there's already a significant object (like a tree).

                // TODO: But we might want to allow mushrooms with bushes.

                continue;
            }

            // Check if there are objects (likely trees) nearby.
            // Mushrooms often grow near trees in forest environments.

            auto nearbyObjectsCount{0};

            for (auto checkY = y - 2; checkY <= y + 2; checkY++)
            {
                for (auto checkX = x - 2; checkX <= x + 2; checkX++)
                {
                    // If the coordinates are the same as the current tile.

                    if (checkX == x && checkY == y)
                    {
                        // Continue to the next tile.

                        continue;
                    }

                    // If the coordinates are invalid.

                    if (!worldArea->IsValidCoordinate(checkX, checkY))
                    {
                        // Continue to the next tile.

                        continue;
                    }

                    // Obtain the tile at the coordinates.

                    auto nearbyTile{worldArea->GetTile(checkX, checkY)};

                    // If the tile is valid and has objects on it.

                    if (nearbyTile && nearbyTile->GetObjectsStack()->GetSize() > 0)
                    {
                        // Increment the number of nearby objects.

                        nearbyObjectsCount++;
                    }
                }
            }

            // Higher probability if there are objects (trees) nearby (forest environment).
            // Mushrooms thrive in forest ecosystems.

            // 6% base probability.

            auto baseProbability{6};

            // +3% per nearby object (tree).

            auto forestBonus{nearbyObjectsCount * 3};

            // Calculate the probability of adding a mushroom.

            auto mushroomProbability{baseProbability + forestBonus};

            // Cap probability at a reasonable maximum.

            if (mushroomProbability > 25)
            {
                mushroomProbability = 25;
            }

            // Check if a random number is less than the probability of adding a mushroom.

            if (GetRandomInt(100) < mushroomProbability)
            {
                // Make it so that the tile has no other objects on it.

                tile->GetObjectsStack()->ClearObjects();

                // Add a brown mushroom to the tile.

                tile->GetObjectsStack()->AddObject("ObjectBrownMushroom");
            }
        }

        auto numStones{1000 * worldScaling + GetRandomInt(100 * worldScaling)};

        // Create the stones.

        for (auto i = 0; i < numStones; i++)
        {
            auto x{GetRandomInt(worldAreaSize.width)};

            auto y{GetRandomInt(worldAreaSize.height)};

            // Obtain the tile at the random position.

            auto tile{worldArea->GetTile(x, y)};

            if (!tile || tile->GetGround() == Hash("GroundWater") || tile->GetWaterDepth() > 0)
            {
                continue;
            }

            auto objectsStack{tile->GetObjectsStack()};

            if (objectsStack->GetSize() > 0)
            {
                continue;
            }

            objectsStack->ClearObjects();
            objectsStack->AddObject("ObjectStone");
        }
    }
}