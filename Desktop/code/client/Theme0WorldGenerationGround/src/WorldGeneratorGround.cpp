/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "WorldGeneratorGround.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
void WorldGeneratorGround::GenerateGroundWithElevation() const {
  ClearWithDirt();
  GenerateElevationWithBiomes();
  GenerateMountainRanges();
  GenerateValleys();
  GenerateGrassBiomes();
  GenerateRockFormations();
}

void WorldGeneratorGround::ClearWithDirt() const {
  auto worldArea{GetWorldArea()};
  auto worldAreaSize{GetWorldAreaSize()};

  for (auto y = 0; y < worldAreaSize.height; y++) {
    for (auto x = 0; x < worldAreaSize.width; x++) {
      auto tile{worldArea->GetTile(x, y)};

      if (!tile)
        continue;

      tile->SetGround("GroundDirt");
      tile->SetElevation(GetDefaultGroundElevation());
    }
  }
}

int WorldGeneratorGround::GetMaxElevation() const {
  // Maximum elevation cap to prevent excessive stacking.
  return 300;
}

int WorldGeneratorGround::GetMaxSlopePerTile() const {
  // Maximum elevation difference between adjacent tiles.
  // This prevents mountains from becoming too steep.
  return 8;
}

int WorldGeneratorGround::GetMaxAllowedElevation(int x, int y, int currentElevation) const {
  // Calculate the maximum elevation this tile can have based on adjacent tiles
  // to prevent steep slopes. This ensures mountains have gradual slopes.

  auto maxSlope{GetMaxSlopePerTile()};

  // Start with allowing max slope increase from current elevation
  auto maxAllowedElevation{currentElevation + maxSlope};

  // Check all 8 adjacent tiles (including diagonals) to ensure we don't create too steep
  // a slope.

  int directions[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

  for (auto dir = 0; dir < 8; dir++) {
    auto adjacentX{x + directions[dir][0]};
    auto adjacentY{y + directions[dir][1]};

    if (!GetWorldArea()->IsValidCoordinate(adjacentX, adjacentY))
      continue;

    auto adjacentTile{GetWorldArea()->GetTile(adjacentX, adjacentY)};

    if (!adjacentTile)
      continue;

    // Skip water tiles - they have their own elevation rules (set to 0).
    if (adjacentTile->GetGround() == Hash("GroundWater"))
      continue;

    auto adjacentElevation{adjacentTile->GetElevation()};

    // The new elevation should not exceed adjacent tile elevation + max slope.
    // This prevents creating a steep upward slope from the adjacent tile.

    auto maxFromAdjacent{adjacentElevation + maxSlope};

    // Update the maximum allowed elevation if the adjacent tile elevation is lower.
    if (maxFromAdjacent < maxAllowedElevation)
      maxAllowedElevation = maxFromAdjacent;
  }

  return maxAllowedElevation;
}

int WorldGeneratorGround::ClampElevation(int elevation) const {
  auto maxElevation{GetMaxElevation()};

  if (elevation > maxElevation)
    return maxElevation;

  if (elevation < GetDefaultGroundElevation())
    return GetDefaultGroundElevation();

  return elevation;
}
}