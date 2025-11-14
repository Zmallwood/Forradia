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
        m_worldArea = _<Theme0::World>().GetCurrentWorldArea();

        m_size = m_worldArea->GetSize();

        m_scale = _<Theme0::Theme0Properties>().GetWorldScaling();
    }

    float WorldGeneratorBase::GetDistance(int x1, int y1, int x2, int y2) const
    {
        auto dx{static_cast<float>(x2 - x1)};

        auto dy{static_cast<float>(y2 - y1)};

        return std::sqrt(dx * dx + dy * dy);
    }

    int WorldGeneratorBase::GetElevationAt(int x, int y) const
    {
        if (!m_worldArea->IsValidCoordinate(x, y))
        {
            return 0;
        }

        auto tile{m_worldArea->GetTile(x, y)};

        return tile ? tile->GetElevation() : 0;
    }

    bool WorldGeneratorBase::IsValidForWater(int x, int y) const
    {
        if (!m_worldArea->IsValidCoordinate(x, y))
        {
            return false;
        }

        auto tile{m_worldArea->GetTile(x, y)};

        if (!tile)
        {
            return false;
        }

        // Don't place water on high elevation (mountains).

        return tile->GetElevation() < 80;
    }

    bool WorldGeneratorBase::IsValidForTree(int x, int y) const
    {
        if (!m_worldArea->IsValidCoordinate(x, y))
        {
            return false;
        }

        auto tile = m_worldArea->GetTile(x, y);

        if (!tile)
        {
            return false;
        }

        // Trees can't grow in water or on bare rock

        auto ground{tile->GetGround()};

        return ground != Hash("GroundWater") && ground != Hash("GroundRock") &&
               tile->GetWaterDepth() == 0;
    }

    bool WorldGeneratorBase::IsNearWater(int x, int y, int radius) const
    {
        for (auto checkY = y - radius; checkY <= y + radius; checkY++)
        {
            for (auto checkX = x - radius; checkX <= x + radius; checkX++)
            {
                if (!m_worldArea->IsValidCoordinate(checkX, checkY))
                {
                    continue;
                }

                auto tile{m_worldArea->GetTile(checkX, checkY)};

                if (tile && tile->GetGround() == Hash("GroundWater"))
                {
                    auto distance{GetDistance(x, y, checkX, checkY)};

                    if (distance <= radius)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool WorldGeneratorBase::IsAdjacentToWater(int x, int y) const
    {
        // Check all 8 adjacent tiles (including diagonals) for water.

        int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

        for (auto dir = 0; dir < 8; dir++)
        {
            auto adjX{x + directions[dir][0]};

            auto adjY{y + directions[dir][1]};

            if (!m_worldArea->IsValidCoordinate(adjX, adjY))
            {
                continue;
            }

            auto adjTile{m_worldArea->GetTile(adjX, adjY)};

            if (adjTile && adjTile->GetGround() == Hash("GroundWater"))
            {
                return true;
            }
        }

        return false;
    }

    void WorldGeneratorBase::CreateBiomeCluster(int centerX, int centerY, int radius,
                                                StringView groundType) const
    {
        for (auto y = centerY - radius; y <= centerY + radius; y++)
        {
            for (auto x = centerX - radius; x <= centerX + radius; x++)
            {
                if (!m_worldArea->IsValidCoordinate(x, y))
                {
                    continue;
                }

                auto distance{GetDistance(x, y, centerX, centerY)};

                if (distance > radius)
                {
                    continue;
                }

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile)
                {
                    tile->SetGround(groundType);

                    if (tile->GetElevation() < k_defaultGroundElevation)
                    {
                        tile->SetElevation(k_defaultGroundElevation);
                    }
                }
            }
        }
    }
}