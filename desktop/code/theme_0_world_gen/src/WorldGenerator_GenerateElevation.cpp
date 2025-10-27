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
        void WorldGenerator::GenerateElevation() const
        {
            auto numHills{140 + GetRandomInt(30)};

            for (auto i = 0; i < numHills; i++)
            {
                auto xCenter{GetRandomInt(m_size.width)};

                auto yCenter{GetRandomInt(m_size.height)};

                auto maxRadius{5 * m_scale +
                               GetRandomInt(5 * m_scale)};

                for (auto r = maxRadius; r >= 0; r--)
                {
                    for (auto y = yCenter - r;
                         y <= yCenter + r; y++)
                    {
                        for (auto x = xCenter - r;
                             x <= xCenter + r; x++)
                        {
                            if (!m_worldArea
                                     ->IsValidCoordinate(x,
                                                         y))
                            {
                                continue;
                            }

                            auto dX{x - xCenter};

                            auto dY{y - yCenter};

                            if (dX * dX + dY * dY <= r * r)
                            {
                                auto tile{
                                    m_worldArea->GetTile(
                                        x, y)};

                                if (tile &&
                                    tile->GetGround() !=
                                        Hash("ground_"
                                             "water"))
                                {
                                    auto tileN{
                                        m_worldArea
                                            ->GetTile(
                                                x, y - 1)};

                                    auto tileS{
                                        m_worldArea
                                            ->GetTile(
                                                x, y + 1)};

                                    auto tileW{
                                        m_worldArea
                                            ->GetTile(x - 1,
                                                      y)};

                                    auto tileE{
                                        m_worldArea
                                            ->GetTile(x + 1,
                                                      y)};

                                    auto tileNW{
                                        m_worldArea
                                            ->GetTile(
                                                x - 1,
                                                y - 1)};

                                    auto tileNE{
                                        m_worldArea
                                            ->GetTile(
                                                x + 1,
                                                y - 1)};

                                    auto tileSW{
                                        m_worldArea
                                            ->GetTile(
                                                x - 1,
                                                y + 1)};

                                    auto tileSE{
                                        m_worldArea
                                            ->GetTile(
                                                x + 1,
                                                y + 1)};

                                    if ((tileN &&
                                         tileN->GetGround() ==
                                             Hash("groun"
                                                  "d_"
                                                  "wate"
                                                  "r")) ||
                                        (tileS &&
                                         tileS->GetGround() ==
                                             Hash("groun"
                                                  "d_"
                                                  "wate"
                                                  "r")) ||
                                        (tileW &&
                                         tileW->GetGround() ==
                                             Hash("groun"
                                                  "d_"
                                                  "wate"
                                                  "r")) ||
                                        (tileE &&
                                         tileE->GetGround() ==
                                             Hash("groun"
                                                  "d_"
                                                  "wate"
                                                  "r")) ||
                                        (tileNW &&
                                         tileNW->GetGround() ==
                                             Hash("groun"
                                                  "d_"
                                                  "wate"
                                                  "r")) ||
                                        (tileNE &&
                                         tileNE->GetGround() ==
                                             Hash("groun"
                                                  "d_"
                                                  "wate"
                                                  "r")) ||
                                        (tileSW &&
                                         tileSW->GetGround() ==
                                             Hash("groun"
                                                  "d_"
                                                  "wate"
                                                  "r")) ||
                                        (tileSE &&
                                         tileSE->GetGround() ==
                                             Hash("grou"
                                                  "nd_"
                                                  "wate"
                                                  "r")))
                                    {
                                        continue;
                                    }

                                    tile->SetElevation(
                                        tile->GetElevation() +
                                        1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}