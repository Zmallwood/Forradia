//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "Tile.hpp"
#include "WorldArea.hpp"
#include "WorldGeneratorWater.hpp"

namespace Forradia::Theme0 {
    void WorldGeneratorWater::GenerateRiverFromSource(int startX, int startY, int length) const {
        // Obtain required data.

        auto worldArea{GetWorldArea()};

        auto worldAreaSize{GetWorldAreaSize()};

        // Define the minimum river length.

        const auto minRiverLength{20};

        // Define the eight surrounding directions.

        int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

        // Initialize the current position.

        auto currentX{static_cast<float>(startX)};

        auto currentY{static_cast<float>(startY)};

        // Initialize the number of tiles placed.

        auto tilesPlaced{0};

        // Generate the river.

        for (auto step = 0; step < length && tilesPlaced < length; step++) {
            // Get the current position.

            auto x{CInt(currentX)};

            auto y{CInt(currentY)};

            // Validate and clamp coordinates to map bounds.

            // Clamp the coordinates to the map bounds.

            if (x < 0) {
                x = 0;
            }

            // Clamp the coordinates to the map bounds.

            if (x >= worldAreaSize.width) {
                x = worldAreaSize.width - 1;
            }

            // Clamp the coordinates to the map bounds.

            if (y < 0) {
                y = 0;
            }

            // Clamp the coordinates to the map bounds.

            if (y >= worldAreaSize.height) {
                y = worldAreaSize.height - 1;
            }

            // If we're at the edge and have placed enough tiles, stop.

            if ((x == 0 || x == worldAreaSize.width - 1 || y == 0 ||
                 y == worldAreaSize.height - 1) &&
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

            // Get the tile at the current position.

            auto tile{worldArea->GetTile(x, y)};

            if (!tile) {
                // If we've placed enough tiles, stop.

                if (tilesPlaced >= minRiverLength) {
                    break;
                }

                // Continue in a random direction.

                auto angle{GetRandomInt(360) * M_PI / 180.0f};

                currentX += std::cos(angle) * 1.0f;

                currentY += std::sin(angle) * 1.0f;

                continue;
            }

            // Check if we can place water here.
            // Before minimum length, be more lenient.

            auto canPlace{IsValidForWater(x, y)};

            if (!canPlace && tilesPlaced < minRiverLength) {
                // Allow water in slightly higher elevation areas if we haven't reached minimum.

                if (tile->GetElevation() < 90 && tile->GetGround() != Hash("GroundRock")) {
                    canPlace = true;
                }
            }

            // If we can't place water, try to find an adjacent valid tile.

            if (!canPlace) {
                // If we've placed enough tiles, stop.

                if (tilesPlaced >= minRiverLength) {
                    break;
                }

                // Try to find an adjacent valid tile.

                bool foundAdjacent{false};

                // Visit each neighboring tile and update elevation when needed.

                for (auto dir = 0; dir < 8 && !foundAdjacent; dir++) {
                    // Compute the coordinates of the adjacent tile relative to the current
                    // tile.

                    auto adjacentX{x + directions[dir][0]};

                    auto adjacentY{y + directions[dir][1]};

                    // Skip if the adjacent tile is out of bounds.

                    if (worldArea->IsValidCoordinate(adjacentX, adjacentY)) {
                        // Get the adjacent tile.

                        auto adjacentTile{worldArea->GetTile(adjacentX, adjacentY)};

                        // Skip if the adjacent tile is not found.

                        if (adjacentTile && IsValidForWater(adjacentX, adjacentY)) {
                            // Update the current position and tile.

                            x = adjacentX;

                            y = adjacentY;

                            tile = adjacentTile;

                            // Update the current position.

                            currentX = static_cast<float>(x);

                            currentY = static_cast<float>(y);

                            // Set the flag to indicate that we can place water.

                            canPlace = true;

                            // Set the flag to indicate that we found an adjacent valid tile.

                            foundAdjacent = true;
                        }
                    }
                }

                // If we didn't find an adjacent valid tile.

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
                    // Compute the coordinates of the adjacent tile relative to the current
                    // tile.

                    auto adjX{x + directions[dir][0]};

                    auto adjY{y + directions[dir][1]};

                    // Skip if the adjacent tile is out of bounds.

                    if (worldArea->IsValidCoordinate(adjX, adjY) && IsValidForWater(adjX, adjY)) {
                        // Get the adjacent tile.

                        auto adjacentTile{worldArea->GetTile(adjX, adjY)};

                        // Skip if the adjacent tile is not found.

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
                    // Compute the coordinates of the adjacent tile relative to the current
                    // tile.

                    auto checkX{x + directions[dir][0]};

                    auto checkY{y + directions[dir][1]};

                    // Skip if the adjacent tile is out of bounds.

                    if (!worldArea->IsValidCoordinate(checkX, checkY)) {
                        continue;
                    }

                    // Get the adjacent tile.

                    auto checkTile{worldArea->GetTile(checkX, checkY)};

                    // Skip if the adjacent tile is not found.

                    if (!checkTile) {
                        continue;
                    }

                    // Check if it's a valid water placement location.

                    auto canPlaceHere{IsValidForWater(checkX, checkY)};

                    // If the adjacent tile is not a valid water placement location, and we
                    // haven't placed enough tiles, try to place water here.

                    if (!canPlaceHere && tilesPlaced < minRiverLength) {
                        if (checkTile->GetElevation() < 90 &&
                            checkTile->GetGround() != Hash("GroundRock")) {
                            canPlaceHere = true;
                        }
                    }

                    // Skip if the adjacent tile is not a valid water placement location.

                    if (!canPlaceHere) {
                        continue;
                    }

                    // Get the elevation of the adjacent tile.

                    auto checkElevation{checkTile->GetElevation()};

                    // If the elevation of the adjacent tile is lower than the best elevation,
                    // update the best elevation.

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
                    // Update the current position.

                    currentX += bestDX;

                    currentY += bestDY;
                } else {
                    // No clear downhill path - choose a random valid direction.
                    // Rivers don't need to flow downhill, they can flow in any direction.

                    // To hold the result of whether we found a direction.

                    auto foundDirection{false};

                    // Initialize the number of attempts to find a direction.

                    auto attempts{0};

                    // Try to find a direction for 20 attempts.

                    while (!foundDirection && attempts < 20) {
                        // Get a random direction.

                        auto dir{GetRandomInt(8)};

                        // Compute the coordinates of the tile to check.

                        auto checkX{x + directions[dir][0]};

                        auto checkY{y + directions[dir][1]};

                        // If the coordinates are valid.

                        if (worldArea->IsValidCoordinate(checkX, checkY)) {
                            // Get the adjacent tile.

                            auto checkTile{worldArea->GetTile(checkX, checkY)};

                            // If the checked tile is found.

                            if (checkTile) {
                                // Check if the tile is a valid water placement location.

                                auto canPlaceHere{IsValidForWater(checkX, checkY)};

                                // If the tile is not a valid water placement location, and we
                                // haven't placed enough tiles, try to place water here.

                                if (!canPlaceHere && tilesPlaced < minRiverLength) {
                                    // If the tile is a valid water placement location.

                                    if (checkTile->GetElevation() < 90 &&
                                        checkTile->GetGround() != Hash("GroundRock")) {
                                        // Set the flag to indicate that we can place water
                                        // here.

                                        canPlaceHere = true;
                                    }
                                }

                                // If the tile is a valid water placement location.

                                if (canPlaceHere) {
                                    // update the current osition and set the flag to indicate
                                    // that we found a direction.

                                    currentX = static_cast<float>(checkX);

                                    currentY = static_cast<float>(checkY);

                                    foundDirection = true;
                                }
                            }
                        }

                        // Increment the number of attempts.

                        attempts++;
                    }

                    // If we didn't find a direction.

                    if (!foundDirection) {
                        // Just move in a random direction.

                        auto angle{GetRandomInt(360) * M_PI / 180.0f};

                        currentX += std::cos(angle) * 1.0f;

                        currentY += std::sin(angle) * 1.0f;
                    }
                }

                // Stop if we've placed enough tiles and reached very low elevation.

                if (tilesPlaced >= minRiverLength && tile->GetElevation() <= 5) {
                    break;
                }
            }
        }
    }
}