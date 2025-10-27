//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "WorldGenerator.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

namespace Forradia
{
    namespace Theme0
    {
        void WorldGenerator::GenerateRock() const
        {
            auto numRockAreas{30 + GetRandomInt(10)};

            for (auto i = 0; i < numRockAreas; i++)
            {
                auto xCenter{GetRandomInt(m_size.width)};

                auto yCenter{GetRandomInt(m_size.height)};

                auto r{3 * m_scale +
                       GetRandomInt(10 * m_scale)};

                for (auto y = yCenter - r; y <= yCenter + r;
                     y++)
                {
                    for (auto x = xCenter - r;
                         x <= xCenter + r; x++)
                    {
                        if (!m_worldArea->IsValidCoordinate(
                                x, y))
                        {
                            continue;
                        }

                        auto dX{x - xCenter};

                        auto dY{y - yCenter};

                        if (dX * dX + dY * dY <= r * r)
                        {
                            auto tile{
                                m_worldArea->GetTile(x, y)};

                            if (tile->GetElevation() > 0)
                            {
                                tile->SetGround(
                                    "GroundRock");
                            }
                        }
                    }
                }
            }
        }
    }
}