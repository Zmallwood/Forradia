/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "WorldGen.hpp"
#include "GameProps.hpp"
#include "WorldStruct.hpp"

namespace Forradia
{
namespace Theme0
{
    namespace WorldGeneration
    {
        void WorldGenerator::GenerateNewWorld()
        {
            Prepare();

            ClearWithDirt();

            GenerateGrass();

            GenerateLakes();

            GenerateElevation();

            GenerateRock();

            GenerateRivers();

            GenerateObjects();

            GenerateCreatures();

            GenerateNPCs();
        }

        void WorldGenerator::Prepare()
        {
            m_worldArea =
                _<Theme0::WorldStructure::World>().GetCurrentWorldArea();

            m_size = m_worldArea->GetSize();

            m_scale = _<Theme0::GameProperties>().k_worldScaling;
        }

        void WorldGenerator::ClearWithDirt() const
        {
            for (auto y = 0; y < m_size.height; y++)
            {
                for (auto x = 0; x < m_size.width; x++)
                {
                    auto tile{m_worldArea->GetTile(x, y)};

                    if (tile)
                    {
                        tile->SetGround("ground_dirt");
                    }
                }
            }
        }

        void WorldGenerator::GenerateGrass() const
        {
            auto numGrassAreas{50 + GetRandomInt(20)};

            for (auto i = 0; i < numGrassAreas; i++)
            {
                auto xCenter{GetRandomInt(m_size.width)};
                auto yCenter{GetRandomInt(m_size.height)};

                auto radius{3 * m_scale + GetRandomInt(10 * m_scale)};

                for (auto y = yCenter - radius; y <= yCenter + radius; y++)
                {
                    for (auto x = xCenter - radius; x <= xCenter + radius; x++)
                    {
                        if (!m_worldArea->IsValidCoordinate(x, y))
                        {
                            continue;
                        }

                        auto dX{x - xCenter};
                        auto dY{y - yCenter};

                        if (dX * dX + dY * dY <= radius * radius)
                        {
                            auto tile{m_worldArea->GetTile(x, y)};

                            tile->SetGround("ground_grass");
                        }
                    }
                }
            }
        }

        void WorldGenerator::GenerateSingleLake(int minX, int minY, int maxX,
                                                int maxY, int recursion) const
        {
            if (recursion == 0)
            {
                return;
            }

            auto xCenter{minX + GetRandomInt(maxX - minX)};
            auto yCenter{minY + GetRandomInt(maxY - minY)};

            auto maxRadius{CInt(3 * m_scale + GetRandomInt(5 * m_scale))};

            for (auto r = maxRadius; r >= 0; r--)
            {
                for (auto y = yCenter - r; y <= yCenter + r; y++)
                {
                    for (auto x = xCenter - r; x <= xCenter + r; x++)
                    {
                        auto dX{x - xCenter};
                        auto dY{y - yCenter};

                        if (dX * dX + dY * dY <= r * r)
                        {
                            auto tile{m_worldArea->GetTile(x, y)};

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

                                auto tileN{m_worldArea->GetTile(n)};
                                auto tileE{m_worldArea->GetTile(e)};
                                auto tileS{m_worldArea->GetTile(s)};
                                auto tileW{m_worldArea->GetTile(w)};
                                auto tileNW{m_worldArea->GetTile(nw)};
                                auto tileNE{m_worldArea->GetTile(ne)};
                                auto tileSE{m_worldArea->GetTile(se)};
                                auto tileSW{m_worldArea->GetTile(sw)};
                                auto tileNN{m_worldArea->GetTile(nn)};
                                auto tileWW{m_worldArea->GetTile(ww)};
                                auto tileEE{m_worldArea->GetTile(ee)};
                                auto tileSS{m_worldArea->GetTile(ss)};
                                auto tileNWNW{m_worldArea->GetTile(nwnw)};
                                auto tileNENE{m_worldArea->GetTile(nene)};
                                auto tileSESE{m_worldArea->GetTile(sese)};
                                auto tileSWSW{m_worldArea->GetTile(swsw)};

                                auto elevationN{tileN ? tileN->GetElevation()
                                                      : 0};
                                auto elevationE{tileE ? tileE->GetElevation()
                                                      : 0};
                                auto elevationS{tileS ? tileS->GetElevation()
                                                      : 0};
                                auto elevationW{tileW ? tileW->GetElevation()
                                                      : 0};
                                auto elevationNW{tileNW ? tileNW->GetElevation()
                                                        : 0};
                                auto elevationNE{tileNE ? tileNE->GetElevation()
                                                        : 0};
                                auto elevationSE{tileSE ? tileSE->GetElevation()
                                                        : 0};
                                auto elevationSW{tileSW ? tileSW->GetElevation()
                                                        : 0};
                                auto elevationNN{tileNN ? tileNN->GetElevation()
                                                        : 0};
                                auto elevationWW{tileWW ? tileWW->GetElevation()
                                                        : 0};
                                auto elevationEE{tileEE ? tileEE->GetElevation()
                                                        : 0};
                                auto elevationSS{tileSS ? tileSS->GetElevation()
                                                        : 0};
                                auto elevationNWNW{
                                    tileNWNW ? tileNWNW->GetElevation() : 0};
                                auto elevationNENE{
                                    tileNENE ? tileNENE->GetElevation() : 0};
                                auto elevationSESE{
                                    tileSESE ? tileSESE->GetElevation() : 0};
                                auto elevationSWSW{
                                    tileSWSW ? tileSWSW->GetElevation() : 0};

                                if (elevationN == 0 && elevationE == 0 &&
                                    elevationS == 0 && elevationW == 0 &&
                                    elevationNW == 0 && elevationNE == 0 &&
                                    elevationSE == 0 && elevationSW == 0 &&
                                    elevationNN == 0 && elevationWW == 0 &&
                                    elevationEE == 0 && elevationSS == 0 &&
                                    elevationNWNW == 0 && elevationNENE == 0 &&
                                    elevationSESE == 0 && elevationSWSW == 0)
                                {
                                    tile->SetGround("ground_water");
                                }

                                tile->SetWaterDepth(tile->GetWaterDepth() + 1);
                            }
                        }
                    }
                }
            }

            GenerateSingleLake(xCenter - maxRadius, yCenter - maxRadius,
                               xCenter + maxRadius, yCenter + maxRadius,
                               recursion - 1);
        }

        void WorldGenerator::GenerateLakes() const
        {
            auto numLakes{20 + GetRandomInt(5)};

            for (auto i = 0; i < numLakes; i++)
            {
                GenerateSingleLake(0, 0, m_size.width, m_size.height,
                                   2 + GetRandomInt(5));
            }
        }

        void WorldGenerator::GenerateElevation() const
        {
            auto numHills{140 + GetRandomInt(30)};

            for (auto i = 0; i < numHills; i++)
            {
                auto xCenter{GetRandomInt(m_size.width)};
                auto yCenter{GetRandomInt(m_size.height)};

                auto maxRadius{5 * m_scale + GetRandomInt(5 * m_scale)};

                for (auto r = maxRadius; r >= 0; r--)
                {
                    for (auto y = yCenter - r; y <= yCenter + r; y++)
                    {
                        for (auto x = xCenter - r; x <= xCenter + r; x++)
                        {
                            if (!m_worldArea->IsValidCoordinate(x, y))
                            {
                                continue;
                            }

                            auto dX{x - xCenter};
                            auto dY{y - yCenter};

                            if (dX * dX + dY * dY <= r * r)
                            {
                                auto tile{m_worldArea->GetTile(x, y)};

                                if (tile &&
                                    tile->GetGround() != Hash("ground_water"))
                                {
                                    auto tileN{m_worldArea->GetTile(x, y - 1)};
                                    auto tileS{m_worldArea->GetTile(x, y + 1)};
                                    auto tileW{m_worldArea->GetTile(x - 1, y)};
                                    auto tileE{m_worldArea->GetTile(x + 1, y)};
                                    auto tileNW{
                                        m_worldArea->GetTile(x - 1, y - 1)};
                                    auto tileNE{
                                        m_worldArea->GetTile(x + 1, y - 1)};
                                    auto tileSW{
                                        m_worldArea->GetTile(x - 1, y + 1)};
                                    auto tileSE{
                                        m_worldArea->GetTile(x + 1, y + 1)};

                                    if ((tileN && tileN->GetGround() ==
                                                      Hash("ground_water")) ||
                                        (tileS && tileS->GetGround() ==
                                                      Hash("ground_water")) ||
                                        (tileW && tileW->GetGround() ==
                                                      Hash("ground_water")) ||
                                        (tileE && tileE->GetGround() ==
                                                      Hash("ground_water")) ||
                                        (tileNW && tileNW->GetGround() ==
                                                       Hash("ground_water")) ||
                                        (tileNE && tileNE->GetGround() ==
                                                       Hash("ground_water")) ||
                                        (tileSW && tileSW->GetGround() ==
                                                       Hash("ground_water")) ||
                                        (tileSE && tileSE->GetGround() ==
                                                       Hash("ground_water")))
                                    {
                                        continue;
                                    }

                                    // if (tl_n && tl_n->GetElevation() <
                                    // tl->GetElevation())
                                    // {
                                    //     continue;
                                    // }

                                    // if (tl_s && tl_s->GetElevation() <
                                    // tl->GetElevation())
                                    // {
                                    //     continue;
                                    // }

                                    // if (tl_w && tl_w->GetElevation() <
                                    // tl->GetElevation())
                                    // {
                                    //     continue;
                                    // }

                                    // if (tl_e && tl_e->GetElevation() <
                                    // tl->GetElevation())
                                    // {
                                    //     continue;
                                    // }

                                    // if (tl_nw && tl_nw->GetElevation() <
                                    // tl->GetElevation())
                                    // {
                                    //     continue;
                                    // }

                                    // if (tl_ne && tl_ne->GetElevation() <
                                    // tl->GetElevation())
                                    // {
                                    //     continue;
                                    // }

                                    // if (tl_sw && tl_sw->GetElevation() <
                                    // tl->GetElevation())
                                    // {
                                    //     continue;
                                    // }

                                    // if (tl_se && tl_se->GetElevation() <
                                    // tl->GetElevation())
                                    // {
                                    //     continue;
                                    // }

                                    tile->SetElevation(tile->GetElevation() +
                                                       1);
                                }
                            }
                        }
                    }
                }
            }
        }

        void WorldGenerator::GenerateRock() const
        {
            auto numRockAreas{30 + GetRandomInt(10)};

            for (auto i = 0; i < numRockAreas; i++)
            {
                auto xCenter{GetRandomInt(m_size.width)};
                auto yCenter{GetRandomInt(m_size.height)};

                auto r{3 * m_scale + GetRandomInt(10 * m_scale)};

                for (auto y = yCenter - r; y <= yCenter + r; y++)
                {
                    for (auto x = xCenter - r; x <= xCenter + r; x++)
                    {
                        if (!m_worldArea->IsValidCoordinate(x, y))
                        {
                            continue;
                        }

                        auto dX{x - xCenter};
                        auto dY{y - yCenter};

                        if (dX * dX + dY * dY <= r * r)
                        {
                            auto tile{m_worldArea->GetTile(x, y)};

                            if (tile->GetElevation() > 0)
                            {
                                tile->SetGround("ground_rock");
                            }
                        }
                    }
                }
            }
        }

        void WorldGenerator::GenerateRivers() const
        {
            auto numRivers{20 * m_scale + GetRandomInt(5 * m_scale)};

            for (auto i = 0; i < numRivers; i++)
            {
                auto x{CFloat(GetRandomInt(m_size.width))};
                auto y{CFloat(GetRandomInt(m_size.height))};

                auto startAngle{GetRandomInt(360)};

                auto length{45 + GetRandomInt(20)};

                auto prevXCoordinate{-1};
                auto prevYCoordinate{-1};

                SharedPtr<Theme0::WorldStructure::Tile> prevTile;

                for (auto j = 0; j < length; j++)
                {
                    auto angle{startAngle + std::sin(j * M_PI / 10.0f) * 45};

                    auto xCoordinate{CInt(x)};
                    auto yCoordinate{CInt(y)};

                    if (!m_worldArea->IsValidCoordinate(xCoordinate,
                                                        yCoordinate))
                    {
                        continue;
                    }

                    auto tile = m_worldArea->GetTile(xCoordinate, yCoordinate);

                    if (tile && prevTile)
                    {
                        if (xCoordinate == prevXCoordinate &&
                            yCoordinate > prevYCoordinate)
                        {
                            prevTile->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::S);

                            tile->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::N);
                        }
                        else if (xCoordinate == prevXCoordinate &&
                                 yCoordinate < prevYCoordinate)
                        {
                            prevTile->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::N);

                            tile->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::S);
                        }
                        else if (yCoordinate == prevYCoordinate &&
                                 xCoordinate > prevXCoordinate)
                        {
                            prevTile->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::E);

                            tile->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::W);
                        }
                        else if (yCoordinate == prevYCoordinate &&
                                 xCoordinate < prevXCoordinate)
                        {
                            prevTile->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::W);

                            tile->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::E);
                        }
                        else if (yCoordinate < prevYCoordinate &&
                                 xCoordinate > prevXCoordinate)
                        {
                            prevTile->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::NE);

                            tile->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::SW);
                        }
                        else if (yCoordinate > prevYCoordinate &&
                                 xCoordinate > prevXCoordinate)
                        {
                            prevTile->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::SE);

                            tile->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::NW);
                        }
                        else if (yCoordinate < prevYCoordinate &&
                                 xCoordinate < prevXCoordinate)
                        {
                            prevTile->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::NW);

                            tile->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::SE);
                        }
                        else if (yCoordinate > prevYCoordinate &&
                                 xCoordinate < prevXCoordinate)
                        {
                            prevTile->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::SW);

                            tile->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::NE);
                        }
                    }

                    auto dX = std::cos(angle * M_PI / 180.0f);
                    auto dY = std::sin(angle * M_PI / 180.0f);

                    x += dX;
                    y += dY;

                    prevXCoordinate = xCoordinate;
                    prevYCoordinate = yCoordinate;

                    prevTile = tile;
                }
            }
        }

        void WorldGenerator::GenerateObjects() const
        {
            auto numFirTrees{1000 * m_scale + GetRandomInt(50)};

            for (auto i = 0; i < numFirTrees; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && tile->GetGround() != Hash("ground_water") &&
                    tile->GetGround() != Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();
                    tile->GetObjectsStack()->AddTreeObject("object_fir_tree");
                }
            }

            auto numBirchTrees{1000 * m_scale + GetRandomInt(50)};

            for (auto i = 0; i < numBirchTrees; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && tile->GetGround() != Hash("ground_water") &&
                    tile->GetGround() != Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();
                    tile->GetObjectsStack()->AddTreeObject("object_birch_tree");
                }
            }

            auto numBush1s{400 * m_scale + GetRandomInt(100)};

            for (auto i = 0; i < numBush1s; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && tile->GetGround() != Hash("ground_water") &&
                    tile->GetGround() != Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();
                    tile->GetObjectsStack()->AddObject("object_bush1");
                }
            }

            auto numBush2s{400 * m_scale + GetRandomInt(100)};

            for (auto i = 0; i < numBush2s; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && tile->GetGround() != Hash("ground_water") &&
                    tile->GetGround() != Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();
                    tile->GetObjectsStack()->AddObject("object_bush2");
                }
            }

            auto numPinkFlowers{400 * m_scale + GetRandomInt(100)};

            for (auto i = 0; i < numPinkFlowers; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && tile->GetGround() != Hash("ground_water") &&
                    tile->GetGround() != Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();
                    tile->GetObjectsStack()->AddObject("object_pink_flower");
                }
            }

            auto numTallGrasses{400 * m_scale + GetRandomInt(100)};

            for (auto i = 0; i < numTallGrasses; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && tile->GetGround() != Hash("ground_water") &&
                    tile->GetGround() != Hash("ground_rock"))
                {
                    tile->GetObjectsStack()->ClearObjects();
                    tile->GetObjectsStack()->AddObject("object_tall_grass");
                }
            }

            auto numStoneBoulders{200 * m_scale + GetRandomInt(100)};

            for (auto i = 0; i < numStoneBoulders; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && tile->GetWaterDepth() < 4)
                {
                    tile->GetObjectsStack()->ClearObjects();
                    tile->GetObjectsStack()->AddObject("object_stone_boulder");
                }
            }
        }

        void WorldGenerator::GenerateCreatures() const
        {
            auto numRats{200 * m_scale + GetRandomInt(15 * m_scale)};

            for (auto i = 0; i < numRats; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && !tile->GetCreature() &&
                    tile->GetGround() != Hash("ground_water"))
                {
                    auto newCreature =
                        std::make_shared<Theme0::WorldStructure::Creature>(
                            "creature_rat");

                    tile->SetCreature(newCreature);

                    m_worldArea->GetCreaturesMirrorRef().insert(
                        {tile->GetCreature(), {x, y}});
                }
            }

            auto numButterflies{200 * m_scale + GetRandomInt(15 * m_scale)};

            for (auto i = 0; i < numButterflies; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && !tile->GetCreature() &&
                    tile->GetGround() != Hash("ground_water"))
                {
                    auto newCreature =
                        std::make_shared<Theme0::WorldStructure::Creature>(
                            "creature_butterfly");

                    tile->SetCreature(newCreature);

                    m_worldArea->GetCreaturesMirrorRef().insert(
                        {tile->GetCreature(), {x, y}});
                }
            }
        }

        void WorldGenerator::GenerateNPCs() const
        {
            auto numNPC0s{200 * m_scale + GetRandomInt(15 * m_scale)};

            for (auto i = 0; i < numNPC0s; i++)
            {
                auto x{GetRandomInt(m_size.width)};
                auto y{GetRandomInt(m_size.height)};

                auto tile{m_worldArea->GetTile(x, y)};

                if (tile && !tile->GetNPC() &&
                    tile->GetGround() != Hash("ground_water"))
                {
                    auto newNPC =
                        std::make_shared<Theme0::WorldStructure::NPC>("npc0");

                    tile->SetNPC(newNPC);

                    m_worldArea->GetNPCsMirrorRef().insert(
                        {tile->GetNPC(), {x, y}});
                }
            }
        }
    }
}
}