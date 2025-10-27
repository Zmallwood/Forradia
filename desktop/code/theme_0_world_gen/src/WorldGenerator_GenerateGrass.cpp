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
        void WorldGenerator::GenerateGrass() const
        {
            auto numGrassAreas{50 + GetRandomInt(20)};

            for (auto i = 0; i < numGrassAreas; i++)
            {
                auto xCenter{GetRandomInt(m_size.width)};

                auto yCenter{GetRandomInt(m_size.height)};

                auto radius{3 * m_scale +
                            GetRandomInt(10 * m_scale)};

                for (auto y = yCenter - radius;
                     y <= yCenter + radius; y++)
                {
                    for (auto x = xCenter - radius;
                         x <= xCenter + radius; x++)
                    {
                        if (!m_worldArea->IsValidCoordinate(
                                x, y))
                        {
                            continue;
                        }

                        auto dX{x - xCenter};

                        auto dY{y - yCenter};

                        if (dX * dX + dY * dY <=
                            radius * radius)
                        {
                            auto tile{
                                m_worldArea->GetTile(x, y)};

                            tile->SetGround("ground_grass");
                        }
                    }
                }
            }
        }
    }
}