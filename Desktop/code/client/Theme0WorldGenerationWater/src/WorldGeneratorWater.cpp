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
        // Do the steps to generate water.

        GenerateNaturalRivers();

        GenerateLakesInValleys();

        auto worldArea{GetWorldArea()};

        auto worldAreaSize{GetWorldAreaSize()};

        auto numRivers{100 + GetRandomInt(20)};

        for (auto i = 0; i < numRivers; i++)
        {
            // Generate a random starting point.

            auto startX{GetRandomInt(worldAreaSize.width)};

            auto startY{GetRandomInt(worldAreaSize.height)};

            auto currentX{startX};

            auto currentY{startY};

            auto riverLength{10 + GetRandomInt(50)};

            auto previousX{startX};

            auto previousY{startY};

            for (auto j = 0; j < riverLength; j++)
            {
                // Get the tile at the current point.

                auto tile{worldArea->GetTile(currentX, currentY)};

                if (nullptr == tile)
                {
                    break;
                }

                // If the tile is found and the elevation is greater than 0, and the tile is a valid
                // water placement location.

                if (tile && tile->GetElevation() > 0 && IsValidForWater(currentX, currentY))
                {
                    // Set the tile to water.

                    auto dx{currentX - previousX};

                    auto dy{currentY - previousY};

                    if (dx == 0 && dy > 0)
                    {
                        tile->SetRiverDirection1(Directions::North);
                    }
                    else if (dx == 0 && dy < 0)
                    {
                        tile->SetRiverDirection1(Directions::South);
                    }
                    else if (dx > 0 && dy == 0)
                    {
                        tile->SetRiverDirection1(Directions::West);
                    }
                    else if (dx < 0 && dy == 0)
                    {
                        tile->SetRiverDirection1(Directions::East);
                    }

                    auto newDx{0};

                    auto newDy{0};

                    auto direction{GetRandomInt(9)};

                    switch (direction)
                    {
                    case 0:
                        newDx = 0;
                        newDy = 1;
                        break;
                    case 1:
                        newDx = 0;
                        newDy = -1;
                        break;
                    case 2:
                        newDx = 1;
                        newDy = 0;
                        break;
                    case 3:
                        newDx = -1;
                        newDy = 0;
                        break;
                    case 4:
                        newDx = 1;
                        newDy = 1;
                        break;
                    case 5:
                        newDx = 1;
                        newDy = -1;
                        break;
                    case 6:
                        newDx = -1;
                        newDy = 1;
                        break;
                    case 7:
                        newDx = -1;
                        newDy = -1;
                        break;
                    }

                    if (newDx == 0 && newDy > 0)
                    {
                        tile->SetRiverDirection2(Directions::South);
                    }
                    else if (newDx == 0 && newDy < 0)
                    {
                        tile->SetRiverDirection2(Directions::North);
                    }
                    else if (newDx > 0 && newDy == 0)
                    {
                        tile->SetRiverDirection2(Directions::East);
                    }
                    else if (newDx < 0 && newDy == 0)
                    {
                        tile->SetRiverDirection2(Directions::West);
                    }

                    previousX = currentX;

                    previousY = currentY;

                    currentX += newDx;

                    currentY += newDy;
                }
            }
        }
    }

    void WorldGeneratorWater::GenerateNaturalRivers() const
    {
        // Obtain required data.

        auto worldArea{GetWorldArea()};

        auto worldAreaSize{GetWorldAreaSize()};

        // Set the number of rivers to generate.

        auto numRivers{150 + GetRandomInt(100)};

        // Generate the rivers.

        for (auto i = 0; i < numRivers; i++)
        {
            // Initialize the number of attempts to find a starting point.

            auto attempts{0};

            // Initialize the starting coordinates.

            auto startX{0};

            auto startY{0};

            // Initialize the flag to indicate that we found a starting point.

            auto foundStart{false};

            // Vary starting elevations - some high, some medium, some low.

            auto elevationType{GetRandomInt(100)};

            // Initialize the minimum elevation.

            auto minElevation{0};

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
                // Generate a random starting point.

                startX = GetRandomInt(worldAreaSize.width);

                startY = GetRandomInt(worldAreaSize.height);

                // Get the tile at the starting point.

                auto tile{worldArea->GetTile(startX, startY)};

                // If the tile is found and the elevation is greater than the minimum elevation, and
                // the tile is a valid water placement location.

                if (tile && tile->GetElevation() > minElevation && IsValidForWater(startX, startY))
                {
                    // Set the flag to indicate that we found a starting point.

                    foundStart = true;
                }

                // Increment the number of attempts.

                attempts++;
            }

            // If we didn't find a starting point.

            if (!foundStart)
            {
                // Just continue to the next river.

                continue;
            }

            // Obtain the starting elevation.

            auto startElevation{worldArea->GetTile(startX, startY)->GetElevation()};

            // Initialize the base length.

            auto baseLength{40};

            // Initialize the length variation.

            auto lengthVariation{60};

            // Check if the starting elevation is within certain ranges.

            if (startElevation > 40)
            {
                // Increase the base length and the length variation.

                baseLength = 60;

                lengthVariation = 80;
            }
            else if (startElevation > 15)
            {
                // Increase the base length and the length variation.

                baseLength = 50;

                lengthVariation = 70;
            }

            // Generate the length of the river.

            auto length{baseLength + GetRandomInt(lengthVariation)};

            // Generate the river from the source.

            GenerateRiverFromSource(startX, startY, length);
        }
    }

    void WorldGeneratorWater::GenerateLakesInValleys() const
    {
        // Obtain required data.

        auto worldArea{GetWorldArea()};

        auto worldAreaSize{GetWorldAreaSize()};

        auto worldScaling{GetWorldScaling()};

        // Set the number of lakes to generate.

        auto numLakes{12 + GetRandomInt(8)};

        // Generate the lakes.

        for (auto i = 0; i < numLakes; i++)
        {
            // Initialize the number of attempts to find a suitable valley location.

            auto attempts{0};

            // Initialize the center coordinates.

            auto centerX{0};

            auto centerY{0};

            // Initialize the flag to indicate that we found a suitable valley location.

            auto foundLocation{false};

            // Find a suitable valley location.

            while (attempts < 50 && !foundLocation)
            {
                // Generate a random center point.

                centerX = GetRandomInt(worldAreaSize.width);

                centerY = GetRandomInt(worldAreaSize.height);

                // Get the tile at the center point.

                auto tile{worldArea->GetTile(centerX, centerY)};

                // If the tile is found and the elevation is less than or equal to 32, and the tile
                // is not a water tile.

                if (tile && tile->GetElevation() <= 32 && tile->GetGround() != Hash("GroundWater"))
                {
                    // Set the flag to indicate that we found a suitable valley location.

                    foundLocation = true;
                }

                attempts++;
            }

            // If we didn't find a suitable valley location.

            if (!foundLocation)
            {
                // Just continue to the next lake.

                continue;
            }

            // Obtain the radius of the lake.

            auto radius{CInt(3 * worldScaling + GetRandomInt(6 * worldScaling))};

            // Obtain the irregularity of the lake.

            auto irregularity{0.3f + GetRandomInt(20) / 100.0f};

            // Generate the lake.

            for (auto y = centerY - radius; y <= centerY + radius; y++)
            {
                for (auto x = centerX - radius; x <= centerX + radius; x++)
                {
                    // Check if the coordinates are not valid.

                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        // Just continue to the next tile.

                        continue;
                    }

                    // Get the tile at the given coordinates.

                    auto tile{worldArea->GetTile(x, y)};

                    // Skip if the tile is not found.

                    if (!tile)
                    {
                        // Just continue to the next tile.

                        continue;
                    }

                    // If not suitable for water.

                    if (!IsValidForWater(x, y))
                    {
                        // Just continue to the next tile.

                        continue;
                    }

                    // Obtain the distance from the center of the lake.

                    auto distance{GetDistance(x, y, centerX, centerY)};

                    // If the distance is less than or equal to the radius of the lake.

                    if (distance * distance <= radius * radius)
                    {
                        // Set the ground to water.

                        tile->SetGround("GroundWater");

                        // Obtain the depth of the water.

                        auto depth{static_cast<int>((1.0f - distance / radius) * 4.0f) + 1};

                        // Set the water depth.

                        tile->SetWaterDepth(depth);

                        // Lakes always have elevation 0.

                        tile->SetElevation(0);

                        // Set adjacent tiles' elevation to 0 for shoreline effect.

                        SetAdjacentTilesElevationToZero(x, y);
                    }
                }
            }
        }
    }

    bool WorldGeneratorWater::IsValidForWater(int x, int y) const
    {
        // Check if the coordinates are valid.

        if (!GetWorldArea()->IsValidCoordinate(x, y))
        {
            // Return false if not valid.

            return false;
        }

        // Get the tile at the given coordinates.

        auto tile{GetWorldArea()->GetTile(x, y)};

        // Return false if the tile is not found.

        if (!tile)
        {
            // Return false if the tile is not found.

            return false;
        }

        // Don't place water on high elevation (mountains).

        return tile->GetElevation() < 80;
    }
    void WorldGeneratorWater::SetAdjacentTilesElevationToZero(int x, int y) const
    {
        // Set elevation to 0 for all tiles adjacent to a water tile.
        // This creates a shoreline effect where land around water is at sea level.

        // Enumerate all eight surrounding directions for neighbor checks.

        // clang-format off

        int directions[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                             {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

        // clang-format on

        // Visit each neighboring tile and update elevation when needed.

        for (auto dir = 0; dir < 8; dir++)
        {
            // Compute the coordinates of the adjacent tile relative to the water tile.

            auto adjacentX{x + directions[dir][0]};

            auto adjacentY{y + directions[dir][1]};

            // Skip if the adjacent tile is out of bounds.

            if (!GetWorldArea()->IsValidCoordinate(adjacentX, adjacentY))
            {
                continue;
            }

            // Get the adjacent tile.

            auto adjacentTile{GetWorldArea()->GetTile(adjacentX, adjacentY)};

            // Skip if the adjacent tile is not found.

            if (!adjacentTile)
            {
                continue;
            }

            // Only set elevation to 0 for non-water tiles (shoreline).

            if (adjacentTile->GetGround() != Hash("GroundWater"))
            {
                adjacentTile->SetElevation(0);
            }
        }
    }
}