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