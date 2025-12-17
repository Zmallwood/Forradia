/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "ObjectsStack.hpp"
#include "StdAfx.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"
#include "WorldGeneratorObjects.hpp"

namespace Forradia::Theme0 {
auto WorldGeneratorObjects::GenerateObjectsInBiomes() const -> void {
  auto worldArea{GetWorldArea()};
  auto worldAreaSize{worldArea->GetSize()};
  auto worldScaling{GetWorldScaling()};

  // Add scattered objects throughout the world based on biomes.
  // This complements the forests and meadows.

  // Scattered trees outside of forests.

  auto numScatteredTrees{300 * worldScaling + GetRandomInt(150 * worldScaling)};

  for (auto i = 0; i < numScatteredTrees; i++) {
    auto x{GetRandomInt(worldAreaSize.width)};
    auto y{GetRandomInt(worldAreaSize.height)};

    auto tile = worldArea->GetTile(x, y);

    if (!tile || !IsValidForFlora(x, y))
      continue;

    // Check if the tile has grass ground and if the random number is less than 8.
    if (tile->GetGround() == Hash("GroundGrass") && GetRandomInt(100) < 8) {
      tile->GetObjectsStack()->ClearObjects();

      // Add a tree with type of either fir or birch with a 50% chance.

      if (GetRandomInt(100) < 50)
        tile->GetObjectsStack()->AddObject("ObjectFirTree");
      else
        tile->GetObjectsStack()->AddObject("ObjectBirchTree");
    }
  }

  // Scattered bushes.
  auto numScatteredBushes{1000 * worldScaling + GetRandomInt(100 * worldScaling)};

  for (auto i = 0; i < numScatteredBushes; i++) {
    auto x{GetRandomInt(worldAreaSize.width)};
    auto y{GetRandomInt(worldAreaSize.height)};

    auto tile{worldArea->GetTile(x, y)};

    if (!tile || !IsValidForFlora(x, y))
      continue;

    if (GetRandomInt(100) < 8) {
      tile->GetObjectsStack()->ClearObjects();

      // Add a bush with type of either bush1 or bush2 with a 50% chance.
      if (GetRandomInt(100) < 50)
        tile->GetObjectsStack()->AddObject("ObjectBush1");
      else
        tile->GetObjectsStack()->AddObject("ObjectBush2");
    }
  }

  // Stone boulders - prefer higher elevation areas.
  auto numBoulders{150 * worldScaling + GetRandomInt(100 * worldScaling)};

  for (auto i = 0; i < numBoulders; i++) {
    auto x{GetRandomInt(worldAreaSize.width)};
    auto y{GetRandomInt(worldAreaSize.height)};

    auto tile{worldArea->GetTile(x, y)};

    if (!tile || tile->GetWaterDepth() >= 4)
      continue;

    // Make it so that the tile has no other objects on it.
    tile->GetObjectsStack()->ClearObjects();

    // Add a stone boulder to the tile.
    tile->GetObjectsStack()->AddObject("ObjectStoneBoulder");
  }

  // Brown mushrooms - prefer forest areas with trees nearby.
  // Mushrooms grow on forest floors, often near trees.
  auto numMushrooms{600 * worldScaling + GetRandomInt(400 * worldScaling)};

  for (auto i = 0; i < numMushrooms; i++) {
    auto x{GetRandomInt(worldAreaSize.width)};
    auto y{GetRandomInt(worldAreaSize.height)};

    auto tile{worldArea->GetTile(x, y)};

    if (!tile || !IsValidForFlora(x, y))
      continue;

    auto ground{tile->GetGround()};

    // Mushrooms prefer grass or dirt ground.
    if (ground != Hash("GroundGrass") && ground != Hash("GroundDirt"))
      continue;

    // Don't place mushrooms on tiles that already have trees or large objects.
    // (mushrooms are undergrowth, not replacement for trees).

    auto objectsStack{tile->GetObjectsStack()};

    if (objectsStack->GetSize() > 0)
      continue;

    // Check if there are objects (likely trees) nearby.
    // Mushrooms often grow near trees in forest environments.

    auto nearbyObjectsCount{0};

    for (auto checkY = y - 2; checkY <= y + 2; checkY++) {
      for (auto checkX = x - 2; checkX <= x + 2; checkX++) {
        if (checkX == x && checkY == y)
          continue;

        if (!worldArea->IsValidCoordinate(checkX, checkY))
          continue;

        auto nearbyTile{worldArea->GetTile(checkX, checkY)};

        if (nearbyTile && nearbyTile->GetObjectsStack()->GetSize() > 0)
          nearbyObjectsCount++;
      }
    }

    // Higher probability if there are objects (trees) nearby (forest environment).
    // Mushrooms thrive in forest ecosystems.

    auto baseProbability{6};

    // +3% per nearby object (tree).

    auto forestBonus{nearbyObjectsCount * 3};

    auto mushroomProbability{baseProbability + forestBonus};

    if (mushroomProbability > 25)
      mushroomProbability = 25;

    if (GetRandomInt(100) < mushroomProbability) {
      tile->GetObjectsStack()->ClearObjects();
      tile->GetObjectsStack()->AddObject("ObjectBrownMushroom");
    }
  }

  auto numStones{1000 * worldScaling + GetRandomInt(100 * worldScaling)};

  for (auto i = 0; i < numStones; i++) {
    auto x{GetRandomInt(worldAreaSize.width)};
    auto y{GetRandomInt(worldAreaSize.height)};

    auto tile{worldArea->GetTile(x, y)};

    if (!tile || tile->GetGround() == Hash("GroundWater") || tile->GetWaterDepth() > 0)
      continue;

    auto objectsStack{tile->GetObjectsStack()};

    if (objectsStack->GetSize() > 0)
      continue;

    objectsStack->ClearObjects();
    objectsStack->AddObject("ObjectStone");
  }
}
}
