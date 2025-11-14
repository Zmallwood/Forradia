//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorObjects.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorObjects::GenerateObjectsInBiomes() const
    {
        auto worldArea{GetWorldArea()};

        auto size{worldArea->GetSize()};

        auto scale{GetScale()};

        // Add scattered objects throughout the world based on biomes.
        // This complements the forests and meadows.

        // Scattered trees outside of forests.

        auto numScatteredTrees{300 * scale + GetRandomInt(150 * scale)};

        for (auto i = 0; i < numScatteredTrees; i++)
        {
            auto x{GetRandomInt(size.width)};

            auto y{GetRandomInt(size.height)};

            auto tile = worldArea->GetTile(x, y);

            if (!tile || !IsValidForTree(x, y))
            {
                continue;
            }

            // Prefer grass ground for scattered trees.

            if (tile->GetGround() == Hash("GroundGrass") && GetRandomInt(100) < 8)
            {
                tile->GetObjectsStack()->ClearObjects();

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

        auto numScatteredBushes{1000 * scale + GetRandomInt(100 * scale)};

        for (auto i = 0; i < numScatteredBushes; i++)
        {
            auto x{GetRandomInt(size.width)};

            auto y{GetRandomInt(size.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (!tile || !IsValidForTree(x, y))
            {
                continue;
            }

            if (GetRandomInt(100) < 8)
            {
                tile->GetObjectsStack()->ClearObjects();

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

        auto numBoulders{150 * scale + GetRandomInt(100 * scale)};

        for (auto i = 0; i < numBoulders; i++)
        {
            auto x{GetRandomInt(size.width)};

            auto y{GetRandomInt(size.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (!tile || tile->GetWaterDepth() >= 4)
            {
                continue;
            }

            // Higher elevation = more likely to have boulders.

            auto elevation{tile->GetElevation()};

            // 3% base, +1% per 5 elevation.
            auto boulderProbability = 3 + (elevation / 5);

            if (GetRandomInt(100) < boulderProbability)
            {
                tile->GetObjectsStack()->ClearObjects();

                tile->GetObjectsStack()->AddObject("ObjectStoneBoulder");
            }
        }

        // Brown mushrooms - prefer forest areas with trees nearby.
        // Mushrooms grow on forest floors, often near trees.

        auto numMushrooms{600 * scale + GetRandomInt(400 * scale)};

        for (auto i = 0; i < numMushrooms; i++)
        {
            auto x{GetRandomInt(size.width)};

            auto y{GetRandomInt(size.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (!tile || !IsValidForTree(x, y))
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
                // But we might want to allow mushrooms with bushes.

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
                        // Skip the current tile.

                        continue;
                    }

                    if (!worldArea->IsValidCoordinate(checkX, checkY))
                    {
                        continue;
                    }

                    auto nearbyTile{worldArea->GetTile(checkX, checkY)};

                    if (nearbyTile && nearbyTile->GetObjectsStack()->GetSize() > 0)
                    {
                        nearbyObjectsCount++;
                    }
                }
            }

            // Higher probability if there are objects (trees) nearby (forest environment).
            // Mushrooms thrive in forest ecosystems.

            auto baseProbability{6}; // 6% base probability.

            auto forestBonus{nearbyObjectsCount * 3}; // +3% per nearby object (tree).

            auto mushroomProbability{baseProbability + forestBonus};

            // Cap probability at a reasonable maximum.

            if (mushroomProbability > 25)
            {
                mushroomProbability = 25;
            }

            if (GetRandomInt(100) < mushroomProbability)
            {
                tile->GetObjectsStack()->ClearObjects();

                tile->GetObjectsStack()->AddObject("ObjectBrownMushroom");
            }
        }

        // Scattered metal scraps - random remnants across the landscape.

        auto numMetalScraps{10000 * scale + GetRandomInt(120 * scale)};

        for (auto i = 0; i < numMetalScraps; i++)
        {
            auto x{GetRandomInt(size.width)};

            auto y{GetRandomInt(size.height)};

            auto tile{worldArea->GetTile(x, y)};

            if (!tile)
            {
                continue;
            }

            // Avoid placing scraps in water or on submerged tiles.

            if (tile->GetGround() == Hash("GroundWater") || tile->GetWaterDepth() > 0)
            {
                continue;
            }

            // Only place scraps on relatively clear tiles to prevent replacing major objects.

            auto objectsStack{tile->GetObjectsStack()};

            if (objectsStack->GetSize() > 0)
            {
                continue;
            }

            if (GetRandomInt(100) < 5)
            {
                objectsStack->ClearObjects();

                objectsStack->AddObject("ObjectMetalScrap");
            }
        }
    }
}