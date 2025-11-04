//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia::Theme0
{
    void WorldGenerator::GenerateRivers() const
    {
        auto numRivers{20 * m_scale +
                       GetRandomInt(5 * m_scale)};

        for (auto i = 0; i < numRivers; i++)
        {
            auto x{CFloat(GetRandomInt(m_size.width))};

            auto y{CFloat(GetRandomInt(m_size.height))};

            auto startAngle{GetRandomInt(360)};

            auto length{45 + GetRandomInt(20)};

            for (auto j = 0; j < length; j++)
            {
                auto angle{startAngle +
                           std::sin(j * M_PI / 10.0f) * 45};

                auto xCoordinate{CInt(x)};

                auto yCoordinate{CInt(y)};

                if (!m_worldArea->IsValidCoordinate(
                        xCoordinate, yCoordinate))
                {
                    continue;
                }

                auto tile = m_worldArea->GetTile(
                    xCoordinate, yCoordinate);

                if (tile)
                {
                    tile->SetGround("GroundWater");
                }

                auto dX = std::cos(angle * M_PI / 180.0f);

                auto dY = std::sin(angle * M_PI / 180.0f);

                x += dX;

                y += dY;
            }
        }
    }
}