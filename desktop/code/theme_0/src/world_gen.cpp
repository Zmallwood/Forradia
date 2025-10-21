/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_gen.hpp"
#include "game_props.hpp"
#include "world_struct.hpp"

_NS_START_
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
            w_area_ = _<Theme0::WorldStructure::World>().GetCurrentWorldArea();

            sz_ = w_area_->GetSize();

            scale_ = _<Theme0::GameProperties>().k_world_scaling;
        }

        void WorldGenerator::ClearWithDirt() const
        {
            for (auto y = 0; y < sz_.h; y++)
            {
                for (auto x = 0; x < sz_.w; x++)
                {
                    auto tl{w_area_->GetTile(x, y)};

                    if (tl)
                    {
                        tl->SetGround("ground_dirt");
                    }
                }
            }
        }

        void WorldGenerator::GenerateGrass() const
        {
            auto num_grass_areas{50 + GetRandomInt(20)};

            for (auto i = 0; i < num_grass_areas; i++)
            {
                auto x_cent{GetRandomInt(sz_.w)};
                auto y_cent{GetRandomInt(sz_.h)};

                auto r{3 * scale_ + GetRandomInt(10 * scale_)};

                for (auto y = y_cent - r; y <= y_cent + r; y++)
                {
                    for (auto x = x_cent - r; x <= x_cent + r; x++)
                    {
                        if (!w_area_->IsValidCoordinate(x, y))
                        {
                            continue;
                        }

                        auto dx{x - x_cent};
                        auto dy{y - y_cent};

                        if (dx * dx + dy * dy <= r * r)
                        {
                            auto tl{w_area_->GetTile(x, y)};

                            tl->SetGround("ground_grass");
                        }
                    }
                }
            }
        }

        void WorldGenerator::GenerateSingleLake(int min_x, int min_y, int max_x,
                                           int max_y, int recurs) const
        {
            if (recurs == 0)
            {
                return;
            }

            auto x_cent{min_x + GetRandomInt(max_x - min_x)};
            auto y_cent{min_y + GetRandomInt(max_y - min_y)};

            auto max_r{CInt(3 * scale_ + GetRandomInt(5 * scale_))};

            for (auto r = max_r; r >= 0; r--)
            {
                for (auto y = y_cent - r; y <= y_cent + r; y++)
                {
                    for (auto x = x_cent - r; x <= x_cent + r; x++)
                    {
                        auto dx{x - x_cent};
                        auto dy{y - y_cent};

                        if (dx * dx + dy * dy <= r * r)
                        {
                            auto tl{w_area_->GetTile(x, y)};

                            if (tl)
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

                                auto tl_n{w_area_->GetTile(n)};
                                auto tl_e{w_area_->GetTile(e)};
                                auto tl_s{w_area_->GetTile(s)};
                                auto tl_w{w_area_->GetTile(w)};
                                auto tl_nw{w_area_->GetTile(nw)};
                                auto tl_ne{w_area_->GetTile(ne)};
                                auto tl_se{w_area_->GetTile(se)};
                                auto tl_sw{w_area_->GetTile(sw)};
                                auto tl_nn{w_area_->GetTile(nn)};
                                auto tl_ww{w_area_->GetTile(ww)};
                                auto tl_ee{w_area_->GetTile(ee)};
                                auto tl_ss{w_area_->GetTile(ss)};
                                auto tl_nwnw{w_area_->GetTile(nwnw)};
                                auto tl_nene{w_area_->GetTile(nene)};
                                auto tl_sese{w_area_->GetTile(sese)};
                                auto tl_swsw{w_area_->GetTile(swsw)};

                                auto elev_n{tl_n ? tl_n->GetElevation() : 0};
                                auto elev_e{tl_e ? tl_e->GetElevation() : 0};
                                auto elev_s{tl_s ? tl_s->GetElevation() : 0};
                                auto elev_w{tl_w ? tl_w->GetElevation() : 0};
                                auto elev_nw{tl_nw ? tl_nw->GetElevation() : 0};
                                auto elev_ne{tl_ne ? tl_ne->GetElevation() : 0};
                                auto elev_se{tl_se ? tl_se->GetElevation() : 0};
                                auto elev_sw{tl_sw ? tl_sw->GetElevation() : 0};
                                auto elev_nn{tl_nn ? tl_nn->GetElevation() : 0};
                                auto elev_ww{tl_ww ? tl_ww->GetElevation() : 0};
                                auto elev_ee{tl_ee ? tl_ee->GetElevation() : 0};
                                auto elev_ss{tl_ss ? tl_ss->GetElevation() : 0};
                                auto elev_nwnw{tl_nwnw ? tl_nwnw->GetElevation() : 0};
                                auto elev_nene{tl_nene ? tl_nene->GetElevation() : 0};
                                auto elev_sese{tl_sese ? tl_sese->GetElevation() : 0};
                                auto elev_swsw{tl_swsw ? tl_swsw->GetElevation() : 0};

                                if (elev_n == 0 && elev_e == 0 && elev_s == 0 &&
                                    elev_w == 0 && elev_nw == 0 &&
                                    elev_ne == 0 && elev_se == 0 &&
                                    elev_sw == 0 && elev_nn == 0 &&
                                    elev_ww == 0 && elev_ee == 0 &&
                                    elev_ss == 0 && elev_nwnw == 0 &&
                                    elev_nene == 0 && elev_sese == 0 &&
                                    elev_swsw == 0)
                                {
                                    tl->SetGround("ground_water");
                                }

                                tl->SetWaterDepth(tl->GetWaterDepth() + 1);
                            }
                        }
                    }
                }
            }

            GenerateSingleLake(x_cent - max_r, y_cent - max_r, x_cent + max_r,
                            y_cent + max_r, recurs - 1);
        }

        void WorldGenerator::GenerateLakes() const
        {
            auto num_lakes{20 + GetRandomInt(5)};

            for (auto i = 0; i < num_lakes; i++)
            {
                GenerateSingleLake(0, 0, sz_.w, sz_.h, 2 + GetRandomInt(5));
            }
        }

        void WorldGenerator::GenerateElevation() const
        {
            auto num_hills{140 + GetRandomInt(30)};

            for (auto i = 0; i < num_hills; i++)
            {
                auto x_cent{GetRandomInt(sz_.w)};
                auto y_cent{GetRandomInt(sz_.h)};

                auto max_r{5 * scale_ + GetRandomInt(5 * scale_)};

                for (auto r = max_r; r >= 0; r--)
                {
                    for (auto y = y_cent - r; y <= y_cent + r; y++)
                    {
                        for (auto x = x_cent - r; x <= x_cent + r; x++)
                        {
                            if (!w_area_->IsValidCoordinate(x, y))
                            {
                                continue;
                            }

                            auto dx{x - x_cent};
                            auto dy{y - y_cent};

                            if (dx * dx + dy * dy <= r * r)
                            {
                                auto tl{w_area_->GetTile(x, y)};

                                if (tl && tl->GetGround() != Hash("ground_water"))
                                {
                                    auto tl_n{w_area_->GetTile(x, y - 1)};
                                    auto tl_s{w_area_->GetTile(x, y + 1)};
                                    auto tl_w{w_area_->GetTile(x - 1, y)};
                                    auto tl_e{w_area_->GetTile(x + 1, y)};
                                    auto tl_nw{w_area_->GetTile(x - 1, y - 1)};
                                    auto tl_ne{w_area_->GetTile(x + 1, y - 1)};
                                    auto tl_sw{w_area_->GetTile(x - 1, y + 1)};
                                    auto tl_se{w_area_->GetTile(x + 1, y + 1)};

                                    if ((tl_n && tl_n->GetGround() ==
                                                     Hash("ground_water")) ||
                                        (tl_s && tl_s->GetGround() ==
                                                     Hash("ground_water")) ||
                                        (tl_w && tl_w->GetGround() ==
                                                     Hash("ground_water")) ||
                                        (tl_e && tl_e->GetGround() ==
                                                     Hash("ground_water")) ||
                                        (tl_nw && tl_nw->GetGround() ==
                                                      Hash("ground_water")) ||
                                        (tl_ne && tl_ne->GetGround() ==
                                                      Hash("ground_water")) ||
                                        (tl_sw && tl_sw->GetGround() ==
                                                      Hash("ground_water")) ||
                                        (tl_se && tl_se->GetGround() ==
                                                      Hash("ground_water")))
                                    {
                                        continue;
                                    }

                                    if (tl_n && tl_n->GetElevation() < tl->GetElevation())
                                    {
                                        continue;
                                    }

                                    if (tl_s && tl_s->GetElevation() < tl->GetElevation())
                                    {
                                        continue;
                                    }

                                    if (tl_w && tl_w->GetElevation() < tl->GetElevation())
                                    {
                                        continue;
                                    }

                                    if (tl_e && tl_e->GetElevation() < tl->GetElevation())
                                    {
                                        continue;
                                    }

                                    if (tl_nw && tl_nw->GetElevation() < tl->GetElevation())
                                    {
                                        continue;
                                    }

                                    if (tl_ne && tl_ne->GetElevation() < tl->GetElevation())
                                    {
                                        continue;
                                    }

                                    if (tl_sw && tl_sw->GetElevation() < tl->GetElevation())
                                    {
                                        continue;
                                    }

                                    if (tl_se && tl_se->GetElevation() < tl->GetElevation())
                                    {
                                        continue;
                                    }

                                    tl->SetElevation(tl->GetElevation() + 1);
                                }
                            }
                        }
                    }
                }
            }
        }

        void WorldGenerator::GenerateRock() const
        {
            auto num_rock_areas{30 + GetRandomInt(10)};

            for (auto i = 0; i < num_rock_areas; i++)
            {
                auto x_center{GetRandomInt(sz_.w)};
                auto y_center{GetRandomInt(sz_.h)};

                auto r{3 * scale_ + GetRandomInt(10 * scale_)};

                for (auto y = y_center - r; y <= y_center + r; y++)
                {
                    for (auto x = x_center - r; x <= x_center + r; x++)
                    {
                        if (!w_area_->IsValidCoordinate(x, y))
                        {
                            continue;
                        }

                        auto dx{x - x_center};
                        auto dy{y - y_center};

                        if (dx * dx + dy * dy <= r * r)
                        {
                            auto tl{w_area_->GetTile(x, y)};

                            if (tl->GetElevation() > 0)
                            {
                                tl->SetGround("ground_rock");
                            }
                        }
                    }
                }
            }
        }

        void WorldGenerator::GenerateRivers() const
        {
            auto num_rivers{20 * scale_ + GetRandomInt(5 * scale_)};

            for (auto i = 0; i < num_rivers; i++)
            {
                auto x{CFloat(GetRandomInt(sz_.w))};
                auto y{CFloat(GetRandomInt(sz_.h))};

                auto start_angle{GetRandomInt(360)};

                auto len{45 + GetRandomInt(20)};

                auto prev_x_coord{-1};
                auto prev_y_coord{-1};

                SharedPtr<Theme0::WorldStructure::Tile> prev_tl;

                for (auto j = 0; j < len; j++)
                {
                    auto angle{start_angle + std::sin(j * M_PI / 10.0f) * 45};

                    auto x_coord{CInt(x)};
                    auto y_coord{CInt(y)};

                    if (!w_area_->IsValidCoordinate(x_coord, y_coord))
                    {
                        continue;
                    }

                    auto tl = w_area_->GetTile(x_coord, y_coord);

                    if (tl && prev_tl)
                    {
                        if (x_coord == prev_x_coord && y_coord > prev_y_coord)
                        {
                            prev_tl->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::s);

                            tl->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::n);
                        }
                        else if (x_coord == prev_x_coord &&
                                 y_coord < prev_y_coord)
                        {
                            prev_tl->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::n);

                            tl->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::s);
                        }
                        else if (y_coord == prev_y_coord &&
                                 x_coord > prev_x_coord)
                        {
                            prev_tl->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::e);

                            tl->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::w);
                        }
                        else if (y_coord == prev_y_coord &&
                                 x_coord < prev_x_coord)
                        {
                            prev_tl->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::w);

                            tl->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::e);
                        }
                        else if (y_coord < prev_y_coord &&
                                 x_coord > prev_x_coord)
                        {
                            prev_tl->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::ne);

                            tl->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::sw);
                        }
                        else if (y_coord > prev_y_coord &&
                                 x_coord > prev_x_coord)
                        {
                            prev_tl->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::se);

                            tl->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::nw);
                        }
                        else if (y_coord < prev_y_coord &&
                                 x_coord < prev_x_coord)
                        {
                            prev_tl->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::nw);

                            tl->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::se);
                        }
                        else if (y_coord > prev_y_coord &&
                                 x_coord < prev_x_coord)
                        {
                            prev_tl->SetRiverDirection1(
                                Theme0::WorldStructure::Directions::sw);

                            tl->SetRiverDirection2(
                                Theme0::WorldStructure::Directions::ne);
                        }
                    }

                    auto dx = std::cos(angle * M_PI / 180.0f);
                    auto dy = std::sin(angle * M_PI / 180.0f);

                    x += dx;
                    y += dy;

                    prev_x_coord = x_coord;
                    prev_y_coord = y_coord;

                    prev_tl = tl;
                }
            }
        }

        void WorldGenerator::GenerateObjects() const
        {
            auto num_fir_trees{1000 * scale_ + GetRandomInt(50)};

            for (auto i = 0; i < num_fir_trees; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && tl->GetGround() != Hash("ground_water") &&
                    tl->GetGround() != Hash("ground_rock"))
                {
                    tl->GetObjectsStack()->ClearObjects();
                    tl->GetObjectsStack()->AddTreeObject("object_fir_tree");
                }
            }

            auto num_birch_trees{1000 * scale_ + GetRandomInt(50)};

            for (auto i = 0; i < num_birch_trees; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && tl->GetGround() != Hash("ground_water") &&
                    tl->GetGround() != Hash("ground_rock"))
                {
                    tl->GetObjectsStack()->ClearObjects();
                    tl->GetObjectsStack()->AddTreeObject("object_birch_tree");
                }
            }

            auto num_bush_1s{400 * scale_ + GetRandomInt(100)};

            for (auto i = 0; i < num_bush_1s; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && tl->GetGround() != Hash("ground_water") &&
                    tl->GetGround() != Hash("ground_rock"))
                {
                    tl->GetObjectsStack()->ClearObjects();
                    tl->GetObjectsStack()->AddObject("object_bush1");
                }
            }

            auto num_bush_2s{400 * scale_ + GetRandomInt(100)};

            for (auto i = 0; i < num_bush_2s; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && tl->GetGround() != Hash("ground_water") &&
                    tl->GetGround() != Hash("ground_rock"))
                {
                    tl->GetObjectsStack()->ClearObjects();
                    tl->GetObjectsStack()->AddObject("object_bush2");
                }
            }

            auto num_pink_flowers{400 * scale_ + GetRandomInt(100)};

            for (auto i = 0; i < num_pink_flowers; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && tl->GetGround() != Hash("ground_water") &&
                    tl->GetGround() != Hash("ground_rock"))
                {
                    tl->GetObjectsStack()->ClearObjects();
                    tl->GetObjectsStack()->AddObject("object_pink_flower");
                }
            }

            auto num_tall_grasses{400 * scale_ + GetRandomInt(100)};

            for (auto i = 0; i < num_tall_grasses; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && tl->GetGround() != Hash("ground_water") &&
                    tl->GetGround() != Hash("ground_rock"))
                {
                    tl->GetObjectsStack()->ClearObjects();
                    tl->GetObjectsStack()->AddObject("object_tall_grass");
                }
            }

            auto num_stone_boulders{200 * scale_ + GetRandomInt(100)};

            for (auto i = 0; i < num_stone_boulders; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && tl->GetWaterDepth() < 4)
                {
                    tl->GetObjectsStack()->ClearObjects();
                    tl->GetObjectsStack()->AddObject("object_stone_boulder");
                }
            }
        }

        void WorldGenerator::GenerateCreatures() const
        {
            auto num_rats{200 * scale_ + GetRandomInt(15 * scale_)};

            for (auto i = 0; i < num_rats; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && !tl->GetCreature() &&
                    tl->GetGround() != Hash("ground_water"))
                {
                    auto new_crea =
                        std::make_shared<Theme0::WorldStructure::Creature>(
                            "creature_rat");

                    tl->SetCreature(new_crea);

                    w_area_->GetCreaturesMirrorRef().insert(
                        {tl->GetCreature(), {x, y}});
                }
            }

            auto num_butterflies{200 * scale_ + GetRandomInt(15 * scale_)};

            for (auto i = 0; i < num_butterflies; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && !tl->GetCreature() &&
                    tl->GetGround() != Hash("ground_water"))
                {
                    auto new_crea =
                        std::make_shared<Theme0::WorldStructure::Creature>(
                            "creature_butterfly");

                    tl->SetCreature(new_crea);

                    w_area_->GetCreaturesMirrorRef().insert(
                        {tl->GetCreature(), {x, y}});
                }
            }
        }

        void WorldGenerator::GenerateNPCs() const
        {
            auto num_npc_0s{200 * scale_ + GetRandomInt(15 * scale_)};

            for (auto i = 0; i < num_npc_0s; i++)
            {
                auto x{GetRandomInt(sz_.w)};
                auto y{GetRandomInt(sz_.h)};

                auto tl{w_area_->GetTile(x, y)};

                if (tl && !tl->GetNPC() && tl->GetGround() != Hash("ground_water"))
                {
                    auto new_npc =
                        std::make_shared<Theme0::WorldStructure::NPC>("npc0");

                    tl->SetNPC(new_npc);

                    w_area_->GetNPCsMirrorRef().insert({tl->GetNPC(), {x, y}});
                }
            }
        }
    }
}
_NS_END_