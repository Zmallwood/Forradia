/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "WorldGeneratorWater.hpp"

    #include "Content/WorldStructure/Tile.hpp"
    #include "Content/WorldStructure/WorldArea.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorWater::generateRiverFromSource(int startX, int startY, int length) const
        -> void
    {
        auto worldArea{getWorldArea()};
        auto worldAreaSize{getWorldAreaSize()};

        auto currentX{static_cast<float>(startX)};
        auto currentY{static_cast<float>(startY)};
        auto tilesPlaced{0};

        for (auto step = 0; step < length && tilesPlaced < length; step++)
        {
            int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                    {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

            constexpr auto minRiverLength{20};

            auto x{static_cast<int>(currentX)};
            auto y{static_cast<int>(currentY)};

            if (x < 0)
            {
                x = 0;
            }

            if (x >= worldAreaSize.width)
            {
                x = worldAreaSize.width - 1;
            }

            if (y < 0)
            {
                y = 0;
            }

            if (y >= worldAreaSize.height)
            {
                y = worldAreaSize.height - 1;
            }

            if ((x == 0 || x == worldAreaSize.width - 1 || y == 0 ||
                 y == worldAreaSize.height - 1) &&
                tilesPlaced >= minRiverLength)
            {
                // Try to place water at the edge if valid.

                auto edgeTile{worldArea->getTile(x, y)};

                if (edgeTile && isValidForWater(x, y))
                {
                    edgeTile->setGround("GroundWater");
                    edgeTile->setWaterDepth(1);
                    tilesPlaced++;
                }

                break;
            }

            auto tile{worldArea->getTile(x, y)};

            if (!tile)
            {
                if (tilesPlaced >= minRiverLength)
                {
                    break;
                }

                // Continue in a random direction.

                auto angle{getRandomInt(360) * M_PI / 180.0F};

                currentX += static_cast<float>(std::cos(angle) * 1.0F);
                currentY += static_cast<float>(std::sin(angle) * 1.0F);

                continue;
            }

            auto canPlace{isValidForWater(x, y)};

            if (!canPlace && tilesPlaced < minRiverLength)
            {
                // Allow water in slightly higher elevation areas if we haven't reached minimum.
                if (tile->getElevation() < 90 && tile->getGround() != hash("GroundRock"))
                {
                    canPlace = true;
                }
            }

            // If we can't place water, try to find an adjacent valid tile.
            if (!canPlace)
            {
                if (tilesPlaced >= minRiverLength)
                {
                    break;
                }

                bool foundAdjacent{false};

                // Visit each neighboring tile and update elevation when needed.
                for (auto dir = 0; dir < 8 && !foundAdjacent; dir++)
                {
                    auto adjacentX{x + directions[dir][0]};
                    auto adjacentY{y + directions[dir][1]};

                    if (worldArea->isValidCoordinate(adjacentX, adjacentY))
                    {
                        auto adjacentTile{worldArea->getTile(adjacentX, adjacentY)};

                        if (adjacentTile && isValidForWater(adjacentX, adjacentY))
                        {
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

                if (!foundAdjacent)
                {
                    // Continue in a random direction.

                    auto angle{getRandomInt(360) * M_PI / 180.0F};

                    currentX += static_cast<float>(std::cos(angle) * 1.0F);
                    currentY += static_cast<float>(std::sin(angle) * 1.0F);

                    continue;
                }
            }

            // Place water - rivers preserve their elevation.

            tile->setGround("GroundWater");
            tile->setWaterDepth(1 + getRandomInt(2));

            // Note: Rivers do NOT set elevation to 0 - they keep their natural elevation.

            tilesPlaced++;

            // Occasionally create wider river sections.
            if (getRandomInt(100) < 25)
            {
                // Visit each neighboring tile and update elevation when needed.
                for (auto &direction : directions)
                {
                    auto adjX{x + direction[0]};
                    auto adjY{y + direction[1]};

                    if (worldArea->isValidCoordinate(adjX, adjY) && isValidForWater(adjX, adjY))
                    {
                        auto adjacentTile{worldArea->getTile(adjX, adjY)};

                        if (adjacentTile && getRandomInt(100) < 40)
                        {
                            adjacentTile->setGround("GroundWater");
                            adjacentTile->setWaterDepth(1);
                            // Rivers preserve elevation - no elevation change.
                        }
                    }
                }

                // Choose next direction.
                // Prefer downhill but allow other directions (rivers can flow in any
                // direction).

                auto bestDX{0.0F};
                auto bestDY{0.0F};
                auto bestElevation{tile->getElevation()};
                auto foundDownhill{false};

                // First, try to find a downhill direction (preferred but not required).
                for (auto &direction : directions)
                {
                    auto checkX{x + direction[0]};
                    auto checkY{y + direction[1]};

                    if (!worldArea->isValidCoordinate(checkX, checkY))
                    {
                        continue;
                    }

                    auto checkTile{worldArea->getTile(checkX, checkY)};

                    if (!checkTile)
                    {
                        continue;
                    }

                    auto canPlaceHere{isValidForWater(checkX, checkY)};

                    // If the adjacent tile is not a valid water placement location, and we
                    // haven't placed enough tiles, try to place water here.
                    if (!canPlaceHere && tilesPlaced < minRiverLength)
                    {
                        if (checkTile->getElevation() < 90 &&
                            checkTile->getGround() != hash("GroundRock"))
                        {
                            canPlaceHere = true;
                        }
                    }

                    if (!canPlaceHere)
                    {
                        continue;
                    }

                    auto checkElevation{checkTile->getElevation()};

                    if (checkElevation < bestElevation)
                    {
                        // Update the best elevation.
                        bestElevation = checkElevation;

                        // Update the best direction.
                        bestDX = static_cast<float>(direction[0]);
                        bestDY = static_cast<float>(direction[1]);

                        // Set the flag to indicate that we found a downhill direction.
                        foundDownhill = true;
                    }
                }

                // If we found a downhill direction, move in the chosen direction.
                if (foundDownhill)
                {
                    currentX += bestDX;
                    currentY += bestDY;
                }
                else
                {
                    // No clear downhill path - choose a random valid direction.
                    // Rivers don't need to flow downhill, they can flow in any direction.

                    auto foundDirection{false};

                    // Initialize the number of attempts to find a direction.
                    auto attempts{0};

                    // Try to find a direction for 20 attempts.
                    while (!foundDirection && attempts < 20)
                    {
                        auto dir{getRandomInt(8)};

                        auto checkX{x + directions[dir][0]};
                        auto checkY{y + directions[dir][1]};

                        if (worldArea->isValidCoordinate(checkX, checkY))
                        {
                            if (auto checkTile{worldArea->getTile(checkX, checkY)})
                            {
                                auto canPlaceHere{isValidForWater(checkX, checkY)};

                                // If the tile is not a valid water placement location, and we
                                // haven't placed enough tiles, try to place water here.
                                if (!canPlaceHere && tilesPlaced < minRiverLength)
                                {
                                    if (checkTile->getElevation() < 90 &&
                                        checkTile->getGround() != hash("GroundRock"))
                                    {
                                        canPlaceHere = true;
                                    }
                                }

                                if (canPlaceHere)
                                {
                                    currentX = static_cast<float>(checkX);
                                    currentY = static_cast<float>(checkY);

                                    foundDirection = true;
                                }
                            }
                        }

                        attempts++;
                    }

                    if (!foundDirection)
                    {
                        // Just move in a random direction.
                        auto angle{getRandomInt(360) * M_PI / 180.0F};

                        currentX += static_cast<float>(std::cos(angle) * 1.0F);
                        currentY += static_cast<float>(std::sin(angle) * 1.0F);
                    }
                }

                // Stop if we've placed enough tiles and reached very low elevation.
                if (tilesPlaced >= minRiverLength && tile->getElevation() <= 5)
                {
                    break;
                }
            }
        }
    }
}
