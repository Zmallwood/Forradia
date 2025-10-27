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
        void WorldGenerator::GenerateSingleLake(
            int minX, int minY, int maxX, int maxY,
            int recursion) const
        {
            if (recursion == 0)
            {
                return;
            }

            auto xCenter{minX + GetRandomInt(maxX - minX)};

            auto yCenter{minY + GetRandomInt(maxY - minY)};

            auto maxRadius{CInt(3 * m_scale +
                                GetRandomInt(5 * m_scale))};

            for (auto r = maxRadius; r >= 0; r--)
            {
                for (auto y = yCenter - r; y <= yCenter + r;
                     y++)
                {
                    for (auto x = xCenter - r;
                         x <= xCenter + r; x++)
                    {
                        auto dX{x - xCenter};

                        auto dY{y - yCenter};

                        if (dX * dX + dY * dY <= r * r)
                        {
                            auto tile{
                                m_worldArea->GetTile(x, y)};

                            if (tile)
                            {
                                Point n{x, y - 1};
                                Point e{x + 1, y};
                                Point s{x, y + 1};
                                Point w{x - 1, y};
                                Point nw{x - 1, y - 1};
                                Point ne{x + 1, y - 1};
                                Point se{x + 1, y + 1};
                                Point sw{x - 1, y + 1};
                                Point nn{x, y - 2};
                                Point ww{x - 2, y};
                                Point ee{x + 2, y};
                                Point ss{x, y + 2};
                                Point nwnw{x - 2, y - 2};
                                Point nene{x + 2, y - 2};
                                Point sese{x + 2, y + 2};
                                Point swsw{x - 2, y + 2};

                                auto tileN{
                                    m_worldArea->GetTile(
                                        n)};

                                auto tileE{
                                    m_worldArea->GetTile(
                                        e)};

                                auto tileS{
                                    m_worldArea->GetTile(
                                        s)};

                                auto tileW{
                                    m_worldArea->GetTile(
                                        w)};

                                auto tileNW{
                                    m_worldArea->GetTile(
                                        nw)};

                                auto tileNE{
                                    m_worldArea->GetTile(
                                        ne)};

                                auto tileSE{
                                    m_worldArea->GetTile(
                                        se)};

                                auto tileSW{
                                    m_worldArea->GetTile(
                                        sw)};

                                auto tileNN{
                                    m_worldArea->GetTile(
                                        nn)};

                                auto tileWW{
                                    m_worldArea->GetTile(
                                        ww)};

                                auto tileEE{
                                    m_worldArea->GetTile(
                                        ee)};

                                auto tileSS{
                                    m_worldArea->GetTile(
                                        ss)};

                                auto tileNWNW{
                                    m_worldArea->GetTile(
                                        nwnw)};

                                auto tileNENE{
                                    m_worldArea->GetTile(
                                        nene)};

                                auto tileSESE{
                                    m_worldArea->GetTile(
                                        sese)};

                                auto tileSWSW{
                                    m_worldArea->GetTile(
                                        swsw)};

                                auto elevationN{
                                    tileN
                                        ? tileN
                                              ->GetElevation()
                                        : 0};

                                auto elevationE{
                                    tileE
                                        ? tileE
                                              ->GetElevation()
                                        : 0};

                                auto elevationS{
                                    tileS
                                        ? tileS
                                              ->GetElevation()
                                        : 0};

                                auto elevationW{
                                    tileW
                                        ? tileW
                                              ->GetElevation()
                                        : 0};

                                auto elevationNW{
                                    tileNW
                                        ? tileNW
                                              ->GetElevation()
                                        : 0};

                                auto elevationNE{
                                    tileNE
                                        ? tileNE
                                              ->GetElevation()
                                        : 0};

                                auto elevationSE{
                                    tileSE
                                        ? tileSE
                                              ->GetElevation()
                                        : 0};

                                auto elevationSW{
                                    tileSW
                                        ? tileSW
                                              ->GetElevation()
                                        : 0};

                                auto elevationNN{
                                    tileNN
                                        ? tileNN
                                              ->GetElevation()
                                        : 0};

                                auto elevationWW{
                                    tileWW
                                        ? tileWW
                                              ->GetElevation()
                                        : 0};

                                auto elevationEE{
                                    tileEE
                                        ? tileEE
                                              ->GetElevation()
                                        : 0};

                                auto elevationSS{
                                    tileSS
                                        ? tileSS
                                              ->GetElevation()
                                        : 0};

                                auto elevationNWNW{
                                    tileNWNW
                                        ? tileNWNW
                                              ->GetElevation()
                                        : 0};

                                auto elevationNENE{
                                    tileNENE
                                        ? tileNENE
                                              ->GetElevation()
                                        : 0};

                                auto elevationSESE{
                                    tileSESE
                                        ? tileSESE
                                              ->GetElevation()
                                        : 0};

                                auto elevationSWSW{
                                    tileSWSW
                                        ? tileSWSW
                                              ->GetElevation()
                                        : 0};

                                if (elevationN == 0 &&
                                    elevationE == 0 &&
                                    elevationS == 0 &&
                                    elevationW == 0 &&
                                    elevationNW == 0 &&
                                    elevationNE == 0 &&
                                    elevationSE == 0 &&
                                    elevationSW == 0 &&
                                    elevationNN == 0 &&
                                    elevationWW == 0 &&
                                    elevationEE == 0 &&
                                    elevationSS == 0 &&
                                    elevationNWNW == 0 &&
                                    elevationNENE == 0 &&
                                    elevationSESE == 0 &&
                                    elevationSWSW == 0)
                                {
                                    tile->SetGround(
                                        "ground_water");
                                }

                                tile->SetWaterDepth(
                                    tile->GetWaterDepth() +
                                    1);
                            }
                        }
                    }
                }
            }

            this->GenerateSingleLake(
                xCenter - maxRadius, yCenter - maxRadius,
                xCenter + maxRadius, yCenter + maxRadius,
                recursion - 1);
        }
    }
}