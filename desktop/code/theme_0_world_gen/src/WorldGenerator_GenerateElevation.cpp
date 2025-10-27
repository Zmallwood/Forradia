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

                            if (tile &&
                                tile->GetGround() !=
                                    Hash("GroundWater"))
                            {
                                auto tileN{
                                    m_worldArea->GetTile(
                                        x, y - 1)};

                                auto tileS{
                                    m_worldArea->GetTile(
                                        x, y + 1)};

                                auto tileW{
                                    m_worldArea->GetTile(
                                        x - 1, y)};

                                auto tileE{
                                    m_worldArea->GetTile(
                                        x + 1, y)};

                                auto tileNW{
                                    m_worldArea->GetTile(
                                        x - 1, y - 1)};

                                auto tileNE{
                                    m_worldArea->GetTile(
                                        x + 1, y - 1)};

                                auto tileSW{
                                    m_worldArea->GetTile(
                                        x - 1, y + 1)};

                                auto tileSE{
                                    m_worldArea->GetTile(
                                        x + 1, y + 1)};

                                if ((tileN &&
                                     tileN->GetGround() ==
                                         Hash("GroundWa"
                                              "ter")) ||
                                    (tileS &&
                                     tileS->GetGround() ==
                                         Hash("GroundWa"
                                              "ter")) ||
                                    (tileW &&
                                     tileW->GetGround() ==
                                         Hash("GroundWa"
                                              "ter")) ||
                                    (tileE &&
                                     tileE->GetGround() ==
                                         Hash("GroundWa"
                                              "ter")) ||
                                    (tileNW &&
                                     tileNW->GetGround() ==
                                         Hash("GroundWa"
                                              "ter")) ||
                                    (tileNE &&
                                     tileNE->GetGround() ==
                                         Hash("GroundWa"
                                              "ter")) ||
                                    (tileSW &&
                                     tileSW->GetGround() ==
                                         Hash("GroundWa"
                                              "ter")) ||
                                    (tileSE &&
                                     tileSE->GetGround() ==
                                         Hash("GroundWa"
                                              "ter")))
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