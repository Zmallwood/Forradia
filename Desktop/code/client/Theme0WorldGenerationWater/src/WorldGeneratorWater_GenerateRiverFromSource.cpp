/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Tile.hpp"
#include "WorldArea.hpp"
#include "WorldGeneratorWater.hpp"

namespace Forradia::Theme0 {
void WorldGeneratorWater::GenerateRiverFromSource(int startX, int startY, int length) const {
  auto worldArea{GetWorldArea()};
  auto worldAreaSize{GetWorldAreaSize()};

  const auto minRiverLength{20};

  int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

  auto currentX{static_cast<float>(startX)};
  auto currentY{static_cast<float>(startY)};
  auto tilesPlaced{0};

  for (auto step = 0; step < length && tilesPlaced < length; step++) {
    auto x{CInt(currentX)};
    auto y{CInt(currentY)};

    if (x < 0)
      x = 0;

    if (x >= worldAreaSize.width)
      x = worldAreaSize.width - 1;

    if (y < 0)
      y = 0;

    if (y >= worldAreaSize.height)
      y = worldAreaSize.height - 1;

    if ((x == 0 || x == worldAreaSize.width - 1 || y == 0 || y == worldAreaSize.height - 1) &&
        tilesPlaced >= minRiverLength) {
      // Try to place water at the edge if valid.

      auto edgeTile{worldArea->GetTile(x, y)};

      if (edgeTile && IsValidForWater(x, y)) {
        edgeTile->SetGround("GroundWater");
        edgeTile->SetWaterDepth(1);
        tilesPlaced++;
      }

      break;
    }

    auto tile{worldArea->GetTile(x, y)};

    if (!tile) {
      if (tilesPlaced >= minRiverLength)
        break;

      // Continue in a random direction.

      auto angle{GetRandomInt(360) * M_PI / 180.0f};
      currentX += std::cos(angle) * 1.0f;
      currentY += std::sin(angle) * 1.0f;

      continue;
    }

    auto canPlace{IsValidForWater(x, y)};

    if (!canPlace && tilesPlaced < minRiverLength) {
      // Allow water in slightly higher elevation areas if we haven't reached minimum.
      if (tile->GetElevation() < 90 && tile->GetGround() != Hash("GroundRock"))
        canPlace = true;
    }

    // If we can't place water, try to find an adjacent valid tile.
    if (!canPlace) {
      if (tilesPlaced >= minRiverLength)
        break;

      bool foundAdjacent{false};

      // Visit each neighboring tile and update elevation when needed.
      for (auto dir = 0; dir < 8 && !foundAdjacent; dir++) {
        auto adjacentX{x + directions[dir][0]};
        auto adjacentY{y + directions[dir][1]};

        if (worldArea->IsValidCoordinate(adjacentX, adjacentY)) {
          auto adjacentTile{worldArea->GetTile(adjacentX, adjacentY)};

          if (adjacentTile && IsValidForWater(adjacentX, adjacentY)) {
            x = adjacentX;
            y = adjacentY;
            tile = adjacentTile;

            currentX = static_cast<float>(x);
            currentY = static_cast<float>(y);

            canPlace = true;

            foundAdjacent = true;
          }
        }
      }

      if (!foundAdjacent) {
        // Continue in a random direction.

        auto angle{GetRandomInt(360) * M_PI / 180.0f};
        currentX += std::cos(angle) * 1.0f;
        currentY += std::sin(angle) * 1.0f;

        continue;
      }
    }

    // Place water - rivers preserve their elevation.

    tile->SetGround("GroundWater");
    tile->SetWaterDepth(1 + GetRandomInt(2));

    // Note: Rivers do NOT set elevation to 0 - they keep their natural elevation.

    tilesPlaced++;

    // Occasionally create wider river sections.
    if (GetRandomInt(100) < 25) {
      // Visit each neighboring tile and update elevation when needed.
      for (auto dir = 0; dir < 8; dir++) {
        auto adjX{x + directions[dir][0]};
        auto adjY{y + directions[dir][1]};

        if (worldArea->IsValidCoordinate(adjX, adjY) && IsValidForWater(adjX, adjY)) {
          auto adjacentTile{worldArea->GetTile(adjX, adjY)};

          if (adjacentTile && GetRandomInt(100) < 40) {
            adjacentTile->SetGround("GroundWater");
            adjacentTile->SetWaterDepth(1);
            // Rivers preserve elevation - no elevation change.
          }
        }
      }

      // Choose next direction.
      // Prefer downhill but allow other directions (rivers can flow in any
      // direction).

      auto bestDX{0.0f};
      auto bestDY{0.0f};
      auto bestElevation{tile->GetElevation()};
      auto foundDownhill{false};

      // First, try to find a downhill direction (preferred but not required).
      for (auto dir = 0; dir < 8; dir++) {
        auto checkX{x + directions[dir][0]};
        auto checkY{y + directions[dir][1]};

        if (!worldArea->IsValidCoordinate(checkX, checkY))
          continue;

        auto checkTile{worldArea->GetTile(checkX, checkY)};

        if (!checkTile)
          continue;

        auto canPlaceHere{IsValidForWater(checkX, checkY)};

        // If the adjacent tile is not a valid water placement location, and we
        // haven't placed enough tiles, try to place water here.
        if (!canPlaceHere && tilesPlaced < minRiverLength) {
          if (checkTile->GetElevation() < 90 && checkTile->GetGround() != Hash("GroundRock"))
            canPlaceHere = true;
        }

        if (!canPlaceHere)
          continue;

        auto checkElevation{checkTile->GetElevation()};

        if (checkElevation < bestElevation) {
          // Update the best elevation.
          bestElevation = checkElevation;

          // Update the best direction.
          bestDX = static_cast<float>(directions[dir][0]);
          bestDY = static_cast<float>(directions[dir][1]);

          // Set the flag to indicate that we found a downhill direction.
          foundDownhill = true;
        }
      }

      // If we found a downhill direction, move in the chosen direction.
      if (foundDownhill) {
        currentX += bestDX;
        currentY += bestDY;
      } else {
        // No clear downhill path - choose a random valid direction.
        // Rivers don't need to flow downhill, they can flow in any direction.

        auto foundDirection{false};

        // Initialize the number of attempts to find a direction.
        auto attempts{0};

        // Try to find a direction for 20 attempts.
        while (!foundDirection && attempts < 20) {
          auto dir{GetRandomInt(8)};

          auto checkX{x + directions[dir][0]};
          auto checkY{y + directions[dir][1]};

          if (worldArea->IsValidCoordinate(checkX, checkY)) {

            auto checkTile{worldArea->GetTile(checkX, checkY)};

            if (checkTile) {
              auto canPlaceHere{IsValidForWater(checkX, checkY)};

              // If the tile is not a valid water placement location, and we
              // haven't placed enough tiles, try to place water here.
              if (!canPlaceHere && tilesPlaced < minRiverLength) {
                if (checkTile->GetElevation() < 90 && checkTile->GetGround() != Hash("GroundRock"))
                  canPlaceHere = true;
              }

              if (canPlaceHere) {
                currentX = static_cast<float>(checkX);
                currentY = static_cast<float>(checkY);
                foundDirection = true;
              }
            }
          }

          attempts++;
        }

        if (!foundDirection) {
          // Just move in a random direction.
          auto angle{GetRandomInt(360) * M_PI / 180.0f};
          currentX += std::cos(angle) * 1.0f;
          currentY += std::sin(angle) * 1.0f;
        }
      }

      // Stop if we've placed enough tiles and reached very low elevation.
      if (tilesPlaced >= minRiverLength && tile->GetElevation() <= 5)
        break;
    }
  }
}
}