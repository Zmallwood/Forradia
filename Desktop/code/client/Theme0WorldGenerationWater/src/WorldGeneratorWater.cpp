//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorWater.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorWater::GenerateWater() const
    {
        GenerateNaturalRivers();

        GenerateLakesInValleys();
    }

    void WorldGeneratorWater::GenerateNaturalRivers() const
    {
        auto worldArea{GetWorldArea()};

        auto size{GetSize()};

        // Generate rivers from various elevations.

        auto numRivers{150 + GetRandomInt(100)};

        for (auto i = 0; i < numRivers; i++)
        {
            auto attempts = 0;

            int startX = 0;

            int startY = 0;

            bool foundStart = false;

            // Vary starting elevations - some high, some medium, some low.

            auto elevationType = GetRandomInt(100);

            int minElevation = 0;

            if (elevationType < 40)
            {
                // 40% start from high elevation.

                minElevation = 50;
            }
            else if (elevationType < 70)
            {
                // 30% start from medium elevation.

                minElevation = 20;
            }
            else
            {
                // 30% start from lower elevation.

                minElevation = 5;
            }

            // Find a starting point.

            while (attempts < 100 && !foundStart)
            {
                startX = GetRandomInt(size.width);

                startY = GetRandomInt(size.height);

                auto tile = worldArea->GetTile(startX, startY);

                if (tile && tile->GetElevation() > minElevation && IsValidForWater(startX, startY))
                {
                    foundStart = true;
                }

                attempts++;
            }

            if (!foundStart)
            {
                continue;
            }

            // Determine river length based on starting elevation.

            auto startElevation = worldArea->GetTile(startX, startY)->GetElevation();

            int baseLength = 40;

            int lengthVariation = 60;

            if (startElevation > 40)
            {
                baseLength = 60;

                lengthVariation = 80;
            }
            else if (startElevation > 15)
            {
                baseLength = 50;

                lengthVariation = 70;
            }

            auto length{baseLength + GetRandomInt(lengthVariation)};

            GenerateRiverFromSource(startX, startY, length);
        }
    }

    void WorldGeneratorWater::GenerateRiverFromSource(int startX, int startY, int length) const
    {
        auto worldArea{GetWorldArea()};

        auto size{GetSize()};

        const int minRiverLength = 20;

        auto currentX = static_cast<float>(startX);

        auto currentY = static_cast<float>(startY);

        int tilesPlaced = 0;

        for (auto step = 0; step < length && tilesPlaced < length; step++)
        {
            auto x = CInt(currentX);

            auto y = CInt(currentY);

            // Validate and clamp coordinates to map bounds.

            if (x < 0)
            {
                x = 0;
            }

            if (x >= size.width)
            {
                x = size.width - 1;
            }

            if (y < 0)
            {
                y = 0;
            }

            if (y >= size.height)
            {
                y = size.height - 1;
            }

            // If we're at the edge and have placed enough tiles, we can stop.

            if ((x == 0 || x == size.width - 1 || y == 0 || y == size.height - 1) &&
                tilesPlaced >= minRiverLength)
            {
                // Still try to place water at the edge if valid.

                auto edgeTile = worldArea->GetTile(x, y);

                if (edgeTile && IsValidForWater(x, y))
                {
                    edgeTile->SetGround("GroundWater");

                    edgeTile->SetWaterDepth(1);

                    tilesPlaced++;
                }
                break;
            }

            auto tile = worldArea->GetTile(x, y);

            if (!tile)
            {
                if (tilesPlaced >= minRiverLength)
                {
                    break;
                }

                // Continue in a random direction.

                auto angle = GetRandomInt(360) * M_PI / 180.0f;

                currentX += std::cos(angle) * 1.0f;

                currentY += std::sin(angle) * 1.0f;

                continue;
            }

            // Check if we can place water here.
            // Before minimum length, be more lenient.

            bool canPlace = IsValidForWater(x, y);

            if (!canPlace && tilesPlaced < minRiverLength)
            {
                // Allow water in slightly higher elevation areas if we haven't reached minimum.

                if (tile->GetElevation() < 90 && tile->GetGround() != Hash("GroundRock"))
                {
                    canPlace = true;
                }
            }

            if (!canPlace)
            {
                if (tilesPlaced >= minRiverLength)
                {
                    break;
                }

                // Try to find an adjacent valid tile.

                bool foundAdjacent = false;

                int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                        {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

                for (auto dir = 0; dir < 8 && !foundAdjacent; dir++)
                {
                    auto adjX = x + directions[dir][0];

                    auto adjY = y + directions[dir][1];

                    if (worldArea->IsValidCoordinate(adjX, adjY))
                    {
                        auto adjTile = worldArea->GetTile(adjX, adjY);

                        if (adjTile && IsValidForWater(adjX, adjY))
                        {
                            x = adjX;

                            y = adjY;

                            tile = adjTile;

                            currentX = static_cast<float>(x);

                            currentY = static_cast<float>(y);

                            canPlace = true;

                            foundAdjacent = true;
                        }
                    }
                }

                if (!foundAdjacent)
                {
                    // Continue in random direction.

                    auto angle = GetRandomInt(360) * M_PI / 180.0f;

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

            if (GetRandomInt(100) < 25)
            {
                int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                        {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

                for (auto dir = 0; dir < 8; dir++)
                {
                    auto adjX = x + directions[dir][0];

                    auto adjY = y + directions[dir][1];

                    if (worldArea->IsValidCoordinate(adjX, adjY) && IsValidForWater(adjX, adjY))
                    {
                        auto adjTile = worldArea->GetTile(adjX, adjY);

                        if (adjTile && GetRandomInt(100) < 40)
                        {
                            adjTile->SetGround("GroundWater");

                            adjTile->SetWaterDepth(1);

                            // Rivers preserve elevation - no elevation change.
                        }
                    }
                }
            }

            // Choose next direction.
            // Prefer downhill but allow other directions (rivers can flow in any direction).

            int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                    {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

            float bestDX = 0.0f;

            float bestDY = 0.0f;

            int bestElevation = tile->GetElevation();

            bool foundDownhill = false;

            // First, try to find a downhill direction (preferred but not required).

            for (auto dir = 0; dir < 8; dir++)
            {
                auto checkX = x + directions[dir][0];

                auto checkY = y + directions[dir][1];

                if (!worldArea->IsValidCoordinate(checkX, checkY))
                {
                    continue;
                }

                auto checkTile = worldArea->GetTile(checkX, checkY);

                if (!checkTile)
                {
                    continue;
                }

                // Check if it's a valid water placement location.

                bool canPlaceHere = IsValidForWater(checkX, checkY);

                if (!canPlaceHere && tilesPlaced < minRiverLength)
                {
                    if (checkTile->GetElevation() < 90 &&
                        checkTile->GetGround() != Hash("GroundRock"))
                    {
                        canPlaceHere = true;
                    }
                }

                if (!canPlaceHere)
                {
                    continue;
                }

                auto checkElevation = checkTile->GetElevation();

                if (checkElevation < bestElevation)
                {
                    bestElevation = checkElevation;

                    bestDX = static_cast<float>(directions[dir][0]);

                    bestDY = static_cast<float>(directions[dir][1]);

                    foundDownhill = true;
                }
            }

            // Move in the chosen direction.

            if (foundDownhill)
            {
                currentX += bestDX;

                currentY += bestDY;
            }
            else
            {
                // No clear downhill path - choose a random valid direction.
                // Rivers don't need to flow downhill, they can flow in any direction.

                bool foundDirection = false;

                int attempts = 0;

                while (!foundDirection && attempts < 20)
                {
                    auto dir = GetRandomInt(8);

                    auto checkX = x + directions[dir][0];

                    auto checkY = y + directions[dir][1];

                    if (worldArea->IsValidCoordinate(checkX, checkY))
                    {
                        auto checkTile = worldArea->GetTile(checkX, checkY);

                        if (checkTile)
                        {
                            bool canPlaceHere = IsValidForWater(checkX, checkY);

                            if (!canPlaceHere && tilesPlaced < minRiverLength)
                            {
                                if (checkTile->GetElevation() < 90 &&
                                    checkTile->GetGround() != Hash("GroundRock"))
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

                    auto angle = GetRandomInt(360) * M_PI / 180.0f;

                    currentX += std::cos(angle) * 1.0f;

                    currentY += std::sin(angle) * 1.0f;
                }
            }

            // Stop if we've placed enough tiles and reached very low elevation.

            if (tilesPlaced >= minRiverLength && tile->GetElevation() <= 5)
            {
                break;
            }
        }
    }

    void WorldGeneratorWater::GenerateLakesInValleys() const
    {
        auto worldArea{GetWorldArea()};

        auto size{GetSize()};

        auto scale{GetScale()};

        // Create lakes in low-lying areas.

        auto numLakes{12 + GetRandomInt(8)};

        for (auto i = 0; i < numLakes; i++)
        {
            auto attempts = 0;

            int centerX = 0;

            int centerY = 0;

            bool foundLocation = false;

            // Find a suitable valley location.

            while (attempts < 50 && !foundLocation)
            {
                centerX = GetRandomInt(size.width);

                centerY = GetRandomInt(size.height);

                auto tile = worldArea->GetTile(centerX, centerY);

                if (tile && tile->GetElevation() <= 32 && tile->GetGround() != Hash("GroundWater"))
                {
                    foundLocation = true;
                }

                attempts++;
            }

            if (!foundLocation)
            {
                continue;
            }

            auto radius{CInt(3 * scale + GetRandomInt(6 * scale))};

            auto irregularity{0.3f + GetRandomInt(20) / 100.0f};

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto tile = worldArea->GetTile(x, y);

                    if (!tile)
                    {
                        continue;
                    }

                    // Skip if not suitable for water.

                    if (!IsValidForWater(x, y))
                    {
                        continue;
                    }

                    auto distance = GetDistance(x, y, centerX, centerY);

                    if (distance * distance <= radius * radius)
                    {
                        // Lakes always have elevation 0.

                        tile->SetGround("GroundWater");

                        auto depth = static_cast<int>((1.0f - distance / radius) * 4.0f) + 1;

                        tile->SetWaterDepth(depth);

                        tile->SetElevation(0);

                        // Set adjacent tiles' elevation to 0 for shoreline effect.

                        SetAdjacentTilesElevationToZero(x, y);
                    }
                }
            }
        }
    }
}