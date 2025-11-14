//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGeneratorBase.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Theme0Properties.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldGeneratorBase::Prepare()
    {
        // Get required world related properties.

        m_worldArea = _<Theme0::World>().GetCurrentWorldArea();

        m_size = m_worldArea->GetSize();

        m_scale = _<Theme0::Theme0Properties>().GetWorldScaling();
    }

    float WorldGeneratorBase::GetDistance(int x1, int y1, int x2, int y2) const
    {
        // Calculate the distance between two points.

        auto dx{static_cast<float>(x2 - x1)};

        auto dy{static_cast<float>(y2 - y1)};

        // Return the distance.

        return std::sqrt(dx * dx + dy * dy);
    }

    int WorldGeneratorBase::GetElevationAt(int x, int y) const
    {
        // Check if the coordinates are valid.

        if (!m_worldArea->IsValidCoordinate(x, y))
        {
            // Return 0 if not valid.

            return 0;
        }

        // Get the tile at the given coordinates.

        auto tile{m_worldArea->GetTile(x, y)};

        // Return the elevation of the tile.

        return tile ? tile->GetElevation() : 0;
    }

    bool WorldGeneratorBase::IsValidForWater(int x, int y) const
    {
        // Check if the coordinates are valid.

        if (!m_worldArea->IsValidCoordinate(x, y))
        {
            // Return false if not valid.

            return false;
        }

        // Get the tile at the given coordinates.

        auto tile{m_worldArea->GetTile(x, y)};

        // Return false if the tile is not found.

        if (!tile)
        {
            // Return false if the tile is not found.

            return false;
        }

        // Don't place water on high elevation (mountains).

        return tile->GetElevation() < 80;
    }

    bool WorldGeneratorBase::IsValidForTree(int x, int y) const
    {
        // Check if the coordinates are valid.

        if (!m_worldArea->IsValidCoordinate(x, y))
        {
            // Return false if not valid.

            return false;
        }

        // Get the tile at the given coordinates.

        auto tile = m_worldArea->GetTile(x, y);

        // Return false if the tile is not found.

        if (!tile)
        {
            // Return false if the tile is not found.

            return false;
        }

        // Get the ground type of the tile.

        auto ground{tile->GetGround()};

        // Trees can't grow in water or on bare rock

        return ground != Hash("GroundWater") && ground != Hash("GroundRock") &&
               tile->GetWaterDepth() == 0;
    }

    bool WorldGeneratorBase::IsNearWater(int x, int y, int radius) const
    {
        // Check all tiles in the radius.

        for (auto checkY = y - radius; checkY <= y + radius; checkY++)
        {
            for (auto checkX = x - radius; checkX <= x + radius; checkX++)
            {
                // Skip if the tile is out of bounds.

                if (!m_worldArea->IsValidCoordinate(checkX, checkY))
                {
                    continue;
                }

                // Get the tile at the given coordinates.

                auto tile{m_worldArea->GetTile(checkX, checkY)};

                // Check if the tile is water.

                if (tile && tile->GetGround() == Hash("GroundWater"))
                {
                    // Calculate the distance between the tile and the given coordinates.

                    auto distance{GetDistance(x, y, checkX, checkY)};

                    // Return true if the distance is less than or equal to the radius.

                    if (distance <= radius)
                    {
                        return true;
                    }
                }
            }
        }

        // Return false if no adjacent tile is water.

        return false;
    }

    bool WorldGeneratorBase::IsAdjacentToWater(int x, int y) const
    {
        // Check all 8 adjacent tiles (including diagonals) for water.

        int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

        // Enumerate all 8 adjacent tiles (including diagonals).

        for (auto dir = 0; dir < 8; dir++)
        {
            // Get the adjacent tile coordinates.

            auto adjacentX{x + directions[dir][0]};

            auto adjacentY{y + directions[dir][1]};

            // Skip if the adjacent tile is out of bounds.

            if (!m_worldArea->IsValidCoordinate(adjacentX, adjacentY))
            {
                continue;
            }

            // Get the adjacent tile.

            auto adjacentTile{m_worldArea->GetTile(adjacentX, adjacentY)};

            // Check if the adjacent tile is water.

            if (adjacentTile && adjacentTile->GetGround() == Hash("GroundWater"))
            {
                // If so, return true.

                return true;
            }
        }

        // Return false if no adjacent tile is water.

        return false;
    }

    void WorldGeneratorBase::CreateBiomeCluster(int centerX, int centerY, int radius,
                                                StringView groundType) const
    {
        // Enumerate all tiles in the radius.

        for (auto y = centerY - radius; y <= centerY + radius; y++)
        {
            for (auto x = centerX - radius; x <= centerX + radius; x++)
            {
                // Skip if the tile is out of bounds.

                if (!m_worldArea->IsValidCoordinate(x, y))
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

                auto tile{m_worldArea->GetTile(x, y)};

                // Set the ground type of the tile.

                if (tile)
                {
                    tile->SetGround(groundType);
                }
            }
        }
    }
}