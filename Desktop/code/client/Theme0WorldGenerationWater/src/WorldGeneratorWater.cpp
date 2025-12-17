/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "WorldGeneratorWater.hpp"
#include "Tile.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
void WorldGeneratorWater::GenerateWater() const {
  GenerateNaturalRivers();
  GenerateLakesInValleys();
}

void WorldGeneratorWater::GenerateNaturalRivers() const {
  auto worldArea{GetWorldArea()};
  auto worldAreaSize{GetWorldAreaSize()};

  auto numRivers{150 + GetRandomInt(100)};

  for (auto i = 0; i < numRivers; i++) {
    auto attempts{0};
    auto startX{0};
    auto startY{0};
    auto foundStart{false};

    // Vary starting elevations - some high, some medium, some low.
    auto elevationType{GetRandomInt(100)};

    auto minElevation{0};

    if (elevationType < 40)
      // 40% start from high elevation.
      minElevation = 50;
    else if (elevationType < 70)
      // 30% start from medium elevation.
      minElevation = 20;
    else
      // 30% start from lower elevation.
      minElevation = 5;

    // Find a starting point.
    while (attempts < 100 && !foundStart) {
      startX = GetRandomInt(worldAreaSize.width);
      startY = GetRandomInt(worldAreaSize.height);
      auto tile{worldArea->GetTile(startX, startY)};

      // If the tile is found and the elevation is greater than the minimum elevation,
      // and the tile is a valid water placement location.
      if (tile && tile->GetElevation() > minElevation && IsValidForWater(startX, startY))
        foundStart = true;

      attempts++;
    }

    if (!foundStart)
      // Just continue to the next river.
      continue;

    auto startElevation{worldArea->GetTile(startX, startY)->GetElevation()};
    auto baseLength{40};
    auto lengthVariation{60};

    if (startElevation > 40) {
      // Increase the base length and the length variation.
      baseLength = 60;
      lengthVariation = 80;
    } else if (startElevation > 15) {
      // Increase the base length and the length variation.
      baseLength = 50;
      lengthVariation = 70;
    }

    auto length{baseLength + GetRandomInt(lengthVariation)};

    GenerateRiverFromSource(startX, startY, length);
  }
}

void WorldGeneratorWater::GenerateLakesInValleys() const {
  auto worldArea{GetWorldArea()};
  auto worldAreaSize{GetWorldAreaSize()};
  auto worldScaling{GetWorldScaling()};
  auto numLakes{12 + GetRandomInt(8)};

  for (auto i = 0; i < numLakes; i++) {
    auto attempts{0};
    auto centerX{0};
    auto centerY{0};

    auto foundLocation{false};

    // Find a suitable valley location.
    while (attempts < 50 && !foundLocation) {
      centerX = GetRandomInt(worldAreaSize.width);
      centerY = GetRandomInt(worldAreaSize.height);

      auto tile{worldArea->GetTile(centerX, centerY)};

      if (tile && tile->GetElevation() <= 32 && tile->GetGround() != Hash("GroundWater"))
        // Set the flag to indicate that we found a suitable valley location.
        foundLocation = true;

      attempts++;
    }

    if (!foundLocation)
      // Just continue to the next lake.
      continue;

    auto radius{CInt(3 * worldScaling + GetRandomInt(6 * worldScaling))};
    auto irregularity{0.3f + GetRandomInt(20) / 100.0f};

    for (auto y = centerY - radius; y <= centerY + radius; y++) {
      for (auto x = centerX - radius; x <= centerX + radius; x++) {
        if (!worldArea->IsValidCoordinate(x, y))
          continue;

        auto tile{worldArea->GetTile(x, y)};

        if (!tile)
          // Just continue to the next tile.
          continue;

        if (!IsValidForWater(x, y))
          // Just continue to the next tile.
          continue;

        auto distance{GetDistance(x, y, centerX, centerY)};

        if (distance * distance <= radius * radius) {
          tile->SetGround("GroundWater");

          auto depth{static_cast<int>((1.0f - distance / radius) * 4.0f) + 1};

          tile->SetWaterDepth(depth);
          tile->SetElevation(0);

          SetAdjacentTilesElevationToZero(x, y);
        }
      }
    }
  }
}

bool WorldGeneratorWater::IsValidForWater(int x, int y) const {
  if (!GetWorldArea()->IsValidCoordinate(x, y))
    return false;

  auto tile{GetWorldArea()->GetTile(x, y)};

  if (!tile)
    return false;

  return tile->GetElevation() < 80;
}
void WorldGeneratorWater::SetAdjacentTilesElevationToZero(int x, int y) const {
  // Set elevation to 0 for all tiles adjacent to a water tile.
  // This creates a shoreline effect where land around water is at sea level.

  // Enumerate all eight surrounding directions for neighbor checks.

  // clang-format off
        int directions[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                             {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
  // clang-format on

  // Visit each neighboring tile and update elevation when needed.
  for (auto dir = 0; dir < 8; dir++) {
    auto adjacentX{x + directions[dir][0]};
    auto adjacentY{y + directions[dir][1]};

    if (!GetWorldArea()->IsValidCoordinate(adjacentX, adjacentY))
      continue;

    auto adjacentTile{GetWorldArea()->GetTile(adjacentX, adjacentY)};

    if (!adjacentTile)
      continue;

    if (adjacentTile->GetGround() != Hash("GroundWater"))
      adjacentTile->SetElevation(0);
  }
}
}