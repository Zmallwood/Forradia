//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorGround.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorGround::GenerateGroundWithElevation() const
    {
        ClearWithDirt();

        GenerateElevationWithBiomes();

        GenerateMountainRanges();

        GenerateValleys();

        GenerateGrassBiomes();

        GenerateRockFormations();
    }

    void WorldGeneratorGround::ClearWithDirt() const
    {
        auto worldArea{GetWorldArea()};

        auto worldAreaSize{GetWorldAreaSize()};

        for (auto y = 0; y < worldAreaSize.height; y++)
        {
            for (auto x = 0; x < worldAreaSize.width; x++)
            {
                auto tile{worldArea->GetTile(x, y)};

                if (tile)
                {
                    tile->SetGround("GroundDirt");

                    tile->SetElevation(GetDefaultGroundElevation());
                }
            }
        }
    }

    void WorldGeneratorGround::GenerateGrassBiomes() const
    {
        auto worldArea{GetWorldArea()};

        auto worldAreaSize{GetWorldAreaSize()};

        auto worldScaling{GetWorldScaling()};

        // Create distinct grass biomes with organic shapes.
        // Grass appears in areas with moderate elevation (not mountains, not deep valleys).

        auto numGrassBiomes{25 + GetRandomInt(15)};

        for (auto i = 0; i < numGrassBiomes; i++)
        {
            auto xCenter{GetRandomInt(worldAreaSize.width)};

            auto yCenter{GetRandomInt(worldAreaSize.height)};

            // Check if this area is suitable for grass (moderate elevation, not water).

            auto tile{worldArea->GetTile(xCenter, yCenter)};

            if (!tile || tile->GetElevation() > 100 || tile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            auto radius{CInt(6 * worldScaling + GetRandomInt(10 * worldScaling))};

            auto density{0.7f + GetRandomInt(30) / 100.0f}; // 0.7 to 1.0.

            CreateBiomeCluster(xCenter, yCenter, radius, "GroundGrass");
        }

        // Also add grass in valleys and low-lying areas naturally.

        for (auto y = 0; y < worldAreaSize.height; y++)
        {
            for (auto x = 0; x < worldAreaSize.width; x++)
            {
                auto tile = worldArea->GetTile(x, y);

                if (!tile)
                {
                    continue;
                }

                // Grass naturally grows in low-lying areas that aren't water.

                if (tile->GetElevation() <= 20 && tile->GetGround() != Hash("GroundWater") &&
                    tile->GetGround() != Hash("GroundRock"))
                {
                    tile->SetGround("GroundGrass");
                }
            }
        }
    }

    void WorldGeneratorGround::GenerateRockFormations() const
    {
        auto worldArea{GetWorldArea()};

        auto worldAreaSize{GetWorldAreaSize()};

        auto worldScaling{GetWorldScaling()};

        // Place rocks on mountain peaks and high elevation areas.

        auto numRockFormations{20 + GetRandomInt(15)};

        for (auto i = 0; i < numRockFormations; i++)
        {
            auto xCenter{GetRandomInt(worldAreaSize.width)};

            auto yCenter{GetRandomInt(worldAreaSize.height)};

            auto tile{worldArea->GetTile(xCenter, yCenter)};

            if (!tile || tile->GetElevation() < 80)
            {
                continue;
            }

            // Create rock formations on high elevation.

            auto radius{CInt(2 * worldScaling + GetRandomInt(5 * worldScaling))};

            for (auto y = yCenter - radius; y <= yCenter + radius; y++)
            {
                for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                {
                    if (!worldArea->IsValidCoordinate(x, y))
                    {
                        continue;
                    }

                    auto distance{GetDistance(x, y, xCenter, yCenter)};

                    if (distance > radius)
                    {
                        continue;
                    }

                    auto rockTile{worldArea->GetTile(x, y)};

                    if (!rockTile || rockTile->GetGround() == Hash("GroundWater"))
                    {
                        continue;
                    }

                    // Higher elevation = more likely to be rock.

                    auto elevation{rockTile->GetElevation()};

                    if (elevation > 60)
                    {
                        rockTile->SetGround("GroundRock");
                    }
                }
            }
        }
    }

    void WorldGeneratorGround::CreateBiomeCluster(int centerX, int centerY, int radius,
                                                  StringView groundType) const
    {
        // Enumerate all tiles in the radius.

        for (auto y = centerY - radius; y <= centerY + radius; y++)
        {
            for (auto x = centerX - radius; x <= centerX + radius; x++)
            {
                // Skip if the tile is out of bounds.

                if (!GetWorldArea()->IsValidCoordinate(x, y))
                {
                    continue;
                }

                // Calculate the distance between the tile and the center of the cluster.

                auto distance{GetDistance(x, y, centerX, centerY)};

                // Skip if the distance is greater than the radius.

                if (distance > radius)
                {
                    continue;
                }

                // Get the tile at the given coordinates.

                auto tile{GetWorldArea()->GetTile(x, y)};

                // Set the ground type of the tile.

                if (tile)
                {
                    tile->SetGround(groundType);
                }
            }
        }
    }

    int WorldGeneratorGround::GetMaxElevation() const
    {
        // Maximum elevation cap to prevent excessive stacking.

        return 300;
    }

    int WorldGeneratorGround::GetMaxSlopePerTile() const
    {
        // Maximum elevation difference between adjacent tiles.
        // This prevents mountains from becoming too steep.

        return 8;
    }

    int WorldGeneratorGround::GetMaxAllowedElevation(int x, int y, int currentElevation) const
    {
        // Calculate the maximum elevation this tile can have based on adjacent tiles
        // to prevent steep slopes. This ensures mountains have gradual slopes.

        auto maxSlope{GetMaxSlopePerTile()};

        // Start with allowing max slope increase from current elevation

        auto maxAllowedElevation{currentElevation + maxSlope};

        // Check all 8 adjacent tiles (including diagonals) to ensure we don't create too steep a
        // slope.

        int directions[8][2]{{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

        for (auto dir = 0; dir < 8; dir++)
        {
            // Get the adjacent tile coordinates.

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

            // Skip water tiles - they have their own elevation rules (set to 0).

            if (adjacentTile->GetGround() == Hash("GroundWater"))
            {
                continue;
            }

            // Get the adjacent tile elevation.

            auto adjacentElevation{adjacentTile->GetElevation()};

            // The new elevation should not exceed adjacent tile elevation + max slope.
            // This prevents creating a steep upward slope from the adjacent tile.

            auto maxFromAdjacent{adjacentElevation + maxSlope};

            // Update the maximum allowed elevation if the adjacent tile elevation is lower.

            if (maxFromAdjacent < maxAllowedElevation)
            {
                maxAllowedElevation = maxFromAdjacent;
            }
        }

        return maxAllowedElevation;
    }

    int WorldGeneratorGround::ClampElevation(int elevation) const
    {
        // Get the maximum elevation.

        auto maxElevation{GetMaxElevation()};

        // Clamp the elevation to the maximum elevation.

        if (elevation > maxElevation)
        {
            return maxElevation;
        }

        // Clamp the elevation to the minimum elevation.

        if (elevation < GetDefaultGroundElevation())
        {
            return GetDefaultGroundElevation();
        }

        // Return the elevation.

        return elevation;
    }

    void WorldGeneratorGround::CreateElevationHill(int centerX, int centerY, int radius,
                                                   int maxElevation) const
    {
        // Traverse the candidate tiles within the bounding square of the hill footprint.

        for (auto y = centerY - radius; y <= centerY + radius; y++)
        {
            for (auto x = centerX - radius; x <= centerX + radius; x++)
            {
                // Skip if the tile is out of bounds.

                if (!GetWorldArea()->IsValidCoordinate(x, y))
                {
                    continue;
                }

                // Calculate the distance from the center of the hill to the tile.

                auto distance{GetDistance(x, y, centerX, centerY)};

                // Skip if the tile is outside of the circular hill radius.

                if (distance > radius)
                {
                    continue;
                }

                // Get the tile.

                auto tile{GetWorldArea()->GetTile(x, y)};

                // Skip if the tile is not found.

                if (!tile)
                {
                    continue;
                }

                // Skip water tiles.

                if (tile->GetGround() == Hash("GroundWater"))
                {
                    // Preserve water elevation to maintain coastlines.

                    continue;
                }

                // Check current elevation for smooth capping.

                auto currentElevation{tile->GetElevation()};

                auto maxElevation{GetMaxElevation()};

                // Skip if already at maximum.

                if (currentElevation >= maxElevation)
                {
                    // Prevent further elevation changes once the cap is reached.

                    continue;
                }

                // Create smooth elevation based on distance.

                auto normalizedDistance{distance / radius};

                auto baseElevationGain{static_cast<float>(
                    (1.0f - normalizedDistance * normalizedDistance) * maxElevation)};

                // Adjust the elevation gain to avoid abrupt height increases near the peak.

                // Apply smooth falloff as we approach the elevation cap.

                // Start reducing gain when we're above 60% of max elevation for a smoother
                // transition.

                auto elevationRatio{static_cast<float>(currentElevation) /
                                    static_cast<float>(maxElevation)};

                // Start falloff at 60 % of max elevation.

                auto falloffStart{0.6f};

                auto smoothScale{1.0f};

                if (elevationRatio >= falloffStart)
                {
                    // Smooth falloff using a smoothstep-like curve for very gradual transition.
                    // When at falloffStart (60%), scale is 1.0.
                    // When at 1.0 (100%), scale is 0.0.

                    auto falloffRange{1.0f - falloffStart};

                    // t goes from 0 to 1.

                    auto t{(elevationRatio - falloffStart) / falloffRange};

                    // Use smoothstep curve: 3t^2 - 2t^3 for smooth S-curve transition.
                    // This gives a smoother, more natural falloff.

                    smoothScale = 1.0f - (t * t * (3.0f - 2.0f * t));
                }

                // Apply smooth scaling to elevation gain.

                auto elevationGain{static_cast<int>(baseElevationGain * smoothScale)};

                // Only add elevation if the scaled gain is meaningful.

                if (elevationGain > 0)
                {
                    // Calculate the target elevation before applying slope limits.

                    auto desiredElevation{currentElevation + elevationGain};

                    // Limit elevation based on adjacent tiles to prevent steep slopes.

                    auto maxAllowedElevation{GetMaxAllowedElevation(x, y, currentElevation)};

                    // Use the minimum of desired elevation and max allowed elevation.

                    auto newElevation{desiredElevation};

                    if (newElevation > maxAllowedElevation)
                    {
                        // Respect the slope constraint when the desired elevation is too high.

                        newElevation = maxAllowedElevation;
                    }

                    // Final safety clamp (elevation cap and minimum).

                    tile->SetElevation(ClampElevation(newElevation));
                }
            }
        }
    }
}