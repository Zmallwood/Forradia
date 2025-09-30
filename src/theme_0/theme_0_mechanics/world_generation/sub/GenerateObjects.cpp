/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GenerateObjects.hpp"
#include "theme_0/theme_0_mechanics/configuration/GameProperties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/ObjectsStack.hpp"
#include "theme_0/theme_0_mechanics/world_structure/Tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/World.hpp"
#include "theme_0/theme_0_mechanics/world_structure/WorldArea.hpp"

namespace Forradia {
  void GenerateObjects() {
    auto worldArea{GetSingleton<World>().GetCurrentWorldArea()};

    auto size{worldArea->GetSize()};

    auto scale{GetSingleton<GameProperties>().k_worldScalingFactor};

    auto numFirTrees{1000 * scale + RandomInt(50)};

    for (auto i = 0; i < numFirTrees; i++) {
      auto x{RandomInt(size.width)};
      auto y{RandomInt(size.height)};

      auto tile{worldArea->GetTile(x, y)};

      if (tile && tile->GetGround() != Hash("GroundWater") &&
          tile->GetGround() != Hash("GroundRock")) {
        tile->GetObjectsStack()->ClearObjects();
        tile->GetObjectsStack()->AddTreeObject("ObjectFirTree");
      }
    }

    auto numBirchTrees{1000 * scale + RandomInt(50)};

    for (auto i = 0; i < numBirchTrees; i++) {
      auto x{RandomInt(size.width)};
      auto y{RandomInt(size.height)};

      auto tile{worldArea->GetTile(x, y)};

      if (tile && tile->GetGround() != Hash("GroundWater") &&
          tile->GetGround() != Hash("GroundRock")) {
        tile->GetObjectsStack()->ClearObjects();
        tile->GetObjectsStack()->AddTreeObject("ObjectBirchTree");
      }
    }

    auto numBush1s{400 * scale + RandomInt(100)};

    for (auto i = 0; i < numBush1s; i++) {
      auto x{RandomInt(size.width)};
      auto y{RandomInt(size.height)};

      auto tile{worldArea->GetTile(x, y)};

      if (tile && tile->GetGround() != Hash("GroundWater") &&
          tile->GetGround() != Hash("GroundRock")) {
        tile->GetObjectsStack()->ClearObjects();
        tile->GetObjectsStack()->AddObject("ObjectBush1");
      }
    }

    auto numBush2s{400 * scale + RandomInt(100)};

    for (auto i = 0; i < numBush2s; i++) {
      auto x{RandomInt(size.width)};
      auto y{RandomInt(size.height)};

      auto tile{worldArea->GetTile(x, y)};

      if (tile && tile->GetGround() != Hash("GroundWater") &&
          tile->GetGround() != Hash("GroundRock")) {
        tile->GetObjectsStack()->ClearObjects();
        tile->GetObjectsStack()->AddObject("ObjectBush2");
      }
    }

    auto numPinkFlowers{400 * scale + RandomInt(100)};

    for (auto i = 0; i < numPinkFlowers; i++) {
      auto x{RandomInt(size.width)};
      auto y{RandomInt(size.height)};

      auto tile{worldArea->GetTile(x, y)};

      if (tile && tile->GetGround() != Hash("GroundWater") &&
          tile->GetGround() != Hash("GroundRock")) {
        tile->GetObjectsStack()->ClearObjects();
        tile->GetObjectsStack()->AddObject("ObjectPinkFlower");
      }
    }

    auto numTallGrasses{400 * scale + RandomInt(100)};

    for (auto i = 0; i < numTallGrasses; i++) {
      auto x{RandomInt(size.width)};
      auto y{RandomInt(size.height)};

      auto tile{worldArea->GetTile(x, y)};

      if (tile && tile->GetGround() != Hash("GroundWater") &&
          tile->GetGround() != Hash("GroundRock")) {
        tile->GetObjectsStack()->ClearObjects();
        tile->GetObjectsStack()->AddObject("ObjectTallGrass");
      }
    }

    auto numStoneBoulders{200 * scale + RandomInt(100)};

    for (auto i = 0; i < numStoneBoulders; i++) {
      auto x{RandomInt(size.width)};
      auto y{RandomInt(size.height)};

      auto tile{worldArea->GetTile(x, y)};

      if (tile && tile->GetWaterDepth() < 4) {
        tile->GetObjectsStack()->ClearObjects();
        tile->GetObjectsStack()->AddObject("ObjectStoneBoulder");
      }
    }
  }
}