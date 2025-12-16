//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "WorldGeneratorObjects.hpp"
#include "ObjectsStack.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
void WorldGeneratorObjects::GenerateObjects() const {
  GenerateForests();
  GenerateMeadows();
  GenerateObjectsInBiomes();
}

void WorldGeneratorObjects::GenerateForests() const {
  auto worldArea{GetWorldArea()};
  auto size{worldArea->GetSize()};
  auto worldScaling{GetWorldScaling()};

  // Create dense forest clusters.
  auto numForests{15 + GetRandomInt(10)};

  for (auto i = 0; i < numForests; i++) {
    auto centerX{GetRandomInt(size.width)};
    auto centerY{GetRandomInt(size.height)};

    auto tile{worldArea->GetTile(centerX, centerY)};

    if (!tile || !IsValidForFlora(centerX, centerY)) {
      continue;
    }

    auto radius{CInt(8 * worldScaling + GetRandomInt(12 * worldScaling))};
    auto treeDensity{0.1f + GetRandomInt(20) / 100.0f};

    auto useFir{GetRandomInt(100) < 60};

    for (auto y = centerY - radius; y <= centerY + radius; y++) {
      for (auto x = centerX - radius; x <= centerX + radius; x++) {
        if (!worldArea->IsValidCoordinate(x, y)) {
          continue;
        }

        if (!IsValidForFlora(x, y)) {
          continue;
        }

        auto distance{GetDistance(x, y, centerX, centerY)};

        if (distance > radius) {
          continue;
        }

        auto normalizedDistance{distance / radius};

        // Calculate the local density. Higher density in center, lower at edges.
        auto localDensity{treeDensity * (1.0f - normalizedDistance * 0.5f)};

        if (GetRandomInt(1000) < static_cast<int>(localDensity * 1000.0f)) {
          auto forestTile{worldArea->GetTile(x, y)};

          if (forestTile) {
            forestTile->GetObjectsStack()->ClearObjects();

            // Check if the forest should use fir or birch trees.
            if (useFir) {
              if (GetRandomInt(100) < 70) {
                forestTile->GetObjectsStack()->AddObject("ObjectFirTree");
              } else {
                forestTile->GetObjectsStack()->AddObject("ObjectBirchTree");
              }
            } else {
              if (GetRandomInt(100) < 70) {
                forestTile->GetObjectsStack()->AddObject("ObjectBirchTree");
              } else {
                forestTile->GetObjectsStack()->AddObject("ObjectFirTree");
              }
            }

            // Add undergrowth in forests.
            if (GetRandomInt(100) < 25) {
              if (GetRandomInt(100) < 50) {
                forestTile->GetObjectsStack()->AddObject("ObjectBush1");
              } else {
                forestTile->GetObjectsStack()->AddObject("ObjectBush2");
              }
            }
          }
        }
      }
    }
  }
}

void WorldGeneratorObjects::GenerateMeadows() const {
  auto worldArea{GetWorldArea()};
  auto size{worldArea->GetSize()};
  auto worldScaling{GetWorldScaling()};

  // Create meadow areas with flowers and tall grass.
  auto numMeadows{20 + GetRandomInt(15)};

  for (auto i = 0; i < numMeadows; i++) {
    auto centerX{GetRandomInt(size.width)};
    auto centerY{GetRandomInt(size.height)};

    auto tile{worldArea->GetTile(centerX, centerY)};

    if (!tile || !IsValidForFlora(centerX, centerY)) {
      continue;
    }

    if (tile->GetGround() != Hash("GroundGrass")) {
      continue;
    }

    auto radius{CInt(5 * worldScaling + GetRandomInt(8 * worldScaling))};

    auto flowerDensity{0.15f + GetRandomInt(15) / 100.0f};

    auto grassDensity{0.2f + GetRandomInt(20) / 100.0f};

    for (auto y = centerY - radius; y <= centerY + radius; y++) {
      for (auto x = centerX - radius; x <= centerX + radius; x++) {
        if (!worldArea->IsValidCoordinate(x, y)) {
          continue;
        }

        if (!IsValidForFlora(x, y)) {
          continue;
        }

        auto meadowTile{worldArea->GetTile(x, y)};

        if (!meadowTile || meadowTile->GetGround() != Hash("GroundGrass")) {
          continue;
        }

        auto distance{GetDistance(x, y, centerX, centerY)};

        if (distance > radius) {
          continue;
        }

        // Add flowers.

        if (GetRandomInt(1000) < static_cast<int>(flowerDensity * 1000.0f)) {
          meadowTile->GetObjectsStack()->ClearObjects();
          meadowTile->GetObjectsStack()->AddObject("ObjectPinkFlower");
        } else if (GetRandomInt(1000) < static_cast<int>(grassDensity * 1000.0f)) {
          meadowTile->GetObjectsStack()->ClearObjects();
          meadowTile->GetObjectsStack()->AddObject("ObjectTallGrass");
        }
      }
    }
  }
}

bool WorldGeneratorObjects::IsValidForFlora(int x, int y) const {
  if (!GetWorldArea()->IsValidCoordinate(x, y)) {
    return false;
  }

  auto tile = GetWorldArea()->GetTile(x, y);

  if (!tile) {
    return false;
  }

  auto ground{tile->GetGround()};

  return ground != Hash("GroundWater") && ground != Hash("GroundRock") &&
         tile->GetWaterDepth() == 0;
}
}