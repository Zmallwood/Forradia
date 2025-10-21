/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_view.hpp"
#include "core.hpp"
#include "render.hpp"
#include "theme_0_core.hpp"
#include "update.hpp"
#include "world_struct.hpp"

_NS_START_
namespace Theme0
{
    namespace GameplayCore
    {
        void WorldView::render() const
        {
            auto grid_sz{calc_grid_sz()};

            auto player_pos{_<PlayerCharacter>().pos()};

            auto w_area{_<World>().curr_w_area()};

            auto extra_rows{8};

            auto wa_sz{w_area->get_sz()};

            auto elev_h{0.1f};

            auto player_elev{
                w_area->get_tl(wa_sz.w - player_pos.x, wa_sz.h - player_pos.y)
                    ->elev()};

            auto rend_tl_sz{0.5f};

            Point3F camera_pos{(wa_sz.w - player_pos.x + 0.5f) * rend_tl_sz,
                             (wa_sz.h - player_pos.y + 0.5f) * rend_tl_sz,
                             player_elev * elev_h};

            static float x_canv, y_canv, w_canv, h_canv;

            static int x_coord, y_coord;

            static int ground{0};

            static SharedPtr<Tile> tl, tl_nw, tl_sw, tl_ne, tl_se, tl_nee, tl_see,
                tl_sese, tl_ses, tl_ss;

            for (auto y = -extra_rows; y < grid_sz.h + extra_rows; y++)
            {
                for (auto x = 0; x < grid_sz.w; x++)
                {
                    x_coord =
                        (wa_sz.w - player_pos.x) - (grid_sz.w - 1) / 2 + x;

                    y_coord =
                        (wa_sz.h - player_pos.y) - (grid_sz.h - 1) / 2 + y;

                    if (!w_area->is_valid_coord(x_coord, y_coord))
                    {
                        continue;
                    }

                    tl = w_area->get_tl(x_coord, y_coord);

                    auto objs_stack{tl->objects_stack()};

                    auto objects{objs_stack->objects()};

                    auto coord_nw{Point{x_coord, y_coord}};
                    auto coord_ne{Point{x_coord + 1, y_coord}};
                    auto coord_sw{Point{x_coord, y_coord + 1}};
                    auto coord_se{Point{x_coord + 1, y_coord + 1}};
                    auto coord_nee{Point{x_coord + 2, y_coord}};
                    auto coord_see{Point{x_coord + 2, y_coord + 1}};
                    auto coord_sese{Point{x_coord + 2, y_coord + 2}};
                    auto coord_ses{Point{x_coord + 1, y_coord + 2}};
                    auto coord_ss{Point{x_coord, y_coord + 2}};

                    if (!w_area->is_valid_coord(coord_nw) ||
                        !w_area->is_valid_coord(coord_ne) ||
                        !w_area->is_valid_coord(coord_sw) ||
                        !w_area->is_valid_coord(coord_se))
                    {
                        continue;
                    }

                    tl_nw = w_area->get_tl(coord_nw);
                    tl_ne = w_area->get_tl(coord_ne);
                    tl_sw = w_area->get_tl(coord_sw);
                    tl_se = w_area->get_tl(coord_se);
                    tl_nee = w_area->get_tl(coord_nee);
                    tl_see = w_area->get_tl(coord_see);
                    tl_sese = w_area->get_tl(coord_sese);
                    tl_ses = w_area->get_tl(coord_ses);
                    tl_ss = w_area->get_tl(coord_ss);

                    ground = tl ? tl->ground() : 0;

                    Vector<float> elevs;

                    auto elev_nw{tl_nw ? tl_nw->elev() : 0.0f};
                    auto elev_ne{tl_ne ? tl_ne->elev() : 0.0f};
                    auto elev_se{tl_se ? tl_se->elev() : 0.0f};
                    auto elev_sw{tl_sw ? tl_sw->elev() : 0.0f};
                    auto elev_nee{tl_nee ? tl_nee->elev() : 0.0f};
                    auto elev_see{tl_see ? tl_see->elev() : 0.0f};
                    auto elev_sese{tl_sese ? tl_sese->elev() : 0.0f};
                    auto elev_ses{tl_ses ? tl_ses->elev() : 0.0f};
                    auto elev_ss{tl_ss ? tl_ss->elev() : 0.0f};

                    elevs.push_back(elev_nw);
                    elevs.push_back(elev_ne);
                    elevs.push_back(elev_nee);
                    elevs.push_back(elev_sw);
                    elevs.push_back(elev_se);
                    elevs.push_back(elev_see);
                    elevs.push_back(elev_ss);
                    elevs.push_back(elev_ses);
                    elevs.push_back(elev_sese);

                    auto elev_avg{(elev_nw + elev_ne + elev_sw + elev_se) / 4};

                    auto ground{tl->ground()};

                    if (ground == Hash("ground_water"))
                    {
                        auto anim_idx{(GetTicks() + ((x_coord + y_coord) * 100)) /
                                      500 % 3};
                        ground =
                            Hash("ground_water_" + std::to_string(anim_idx));
                    }

                    for (auto obj : objects)
                    {
                        auto obj_type{obj->type()};

                        if (obj_type == Hash("object_fir_tree") ||
                            obj_type == Hash("object_birch_tree"))
                        {
                            auto tree_obj{
                                std::static_pointer_cast<Forradia::TreeObject>(
                                    obj)};

                            auto trunk_parts{tree_obj->trunk_parts()};

                            auto needleTypes{tree_obj->needle_types()};

                            auto w_factor{tree_obj->w_factor()};

                            for (auto i = 0; i < trunk_parts.size(); i++)
                            {
                                auto trunk_part{trunk_parts.at(i)};

                                auto needle_type{needleTypes.at(i)};

                                auto w_decr_factor{
                                    0.5f + (trunk_parts.size() - i) /
                                               CFloat(trunk_parts.size()) / 2};

                                auto tree_w{rend_tl_sz * w_factor *
                                            w_decr_factor};

                                auto trunk_part_x{trunk_part.x};
                                auto trunk_part_y{trunk_part.x};

                                trunk_part_x *= CFloat(i) /
                                                trunk_parts.size() *
                                                std::sin(GetTicks() / 700.0f +
                                                         x_coord * y_coord);

                                trunk_part_y *= CFloat(i) /
                                                trunk_parts.size() *
                                                std::sin(GetTicks() / 700.0f +
                                                         x_coord * y_coord);

                                auto trunk_part_x_center{
                                    (x_coord - 1) * rend_tl_sz -
                                    rend_tl_sz / 2 - trunk_part_x * tree_w};

                                auto trunk_part_y_center{
                                    (y_coord - 1) * rend_tl_sz -
                                    rend_tl_sz / 2 - trunk_part_y * tree_w};

                                auto trunk_part_z{trunk_part.y * rend_tl_sz};

                                auto trunk_part_width{rend_tl_sz * 0.2f *
                                                      w_decr_factor};

                                auto trunk_part_height{rend_tl_sz * 0.2f};

                                String trunk_part_name;

                                if (obj_type == Hash("object_fir_tree"))
                                {
                                    trunk_part_name =
                                        "object_fir_tree_trunk_part";
                                }
                                else if (obj_type == Hash("object_birch_tree"))
                                {
                                    trunk_part_name =
                                        "object_birch_tree_trunk_part";
                                }

                                _<Engine::Renderers::ModelRenderer>().draw_model(
                                    Hash(trunk_part_name),
                                    trunk_part_x_center - trunk_part_width / 2,
                                    trunk_part_y_center - trunk_part_width / 2,
                                    elev_avg - trunk_part_z, camera_pos,
                                    elev_h);

                                auto needle_w{tree_w};

                                auto needle_h{rend_tl_sz};

                                if (needle_type)
                                {
                                    _<Engine::Renderers::ModelRenderer>()
                                        .draw_model(needle_type,
                                                    trunk_part_x_center,
                                                    trunk_part_y_center,
                                                    elev_avg - trunk_part_z -
                                                        needle_h / 2,
                                                    camera_pos, elev_h);
                                }
                            }
                        }
                        else
                        {
                            _<Engine::Renderers::ModelRenderer>().draw_model(
                                obj_type,
                                (x_coord - 1) * rend_tl_sz - rend_tl_sz / 2,
                                (y_coord - 1) * rend_tl_sz - rend_tl_sz / 2,
                                elev_avg, camera_pos, elev_h);
                        }
                    }

                    if (x_coord == wa_sz.w - player_pos.x &&
                        y_coord == wa_sz.h - player_pos.y)
                    {
                        _<Engine::Renderers::ModelRenderer>().draw_model(
                            Hash("player"),
                            (x_coord - 1) * rend_tl_sz - rend_tl_sz / 2,
                            (y_coord - 1) * rend_tl_sz - rend_tl_sz / 2,
                            elev_avg, camera_pos, elev_h);
                    }

                    _<Engine::Renderers::GroundRenderer>().draw_tile(
                        ground, x_coord - 1, y_coord - 1, rend_tl_sz,
                        camera_pos, elevs, elev_h);
                }
            }
        }
    }
}
_NS_END_