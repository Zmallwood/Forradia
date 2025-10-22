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
        void WorldView::Render() const
        {
            auto gridSize{CalcGridSize()};

            auto playerPos{_<PlayerCharacter>().GetPosition()};

            auto worldArea{_<World>().GetCurrentWorldArea()};

            auto extraRows{8};

            auto worldAreaSize{worldArea->GetSize()};

            auto elevHeight{0.1f};

            auto playerElev{worldArea
                                ->GetTile(worldAreaSize.width - playerPos.x,
                                          worldAreaSize.height - playerPos.y)
                                ->GetElevation()};

            auto rendTileSize{0.5f};

            Point3F cameraPos{
                (worldAreaSize.width - playerPos.x + 0.5f) * rendTileSize,
                (worldAreaSize.height - playerPos.y + 0.5f) * rendTileSize,
                playerElev * elevHeight};

            for (auto y = -extraRows; y < gridSize.height + extraRows; y++)
            {
                for (auto x = 0; x < gridSize.width; x++)
                {
                    auto xCoordinate{(worldAreaSize.width - playerPos.x) -
                                     (gridSize.width - 1) / 2 + x};

                    auto yCoordinate{(worldAreaSize.height - playerPos.y) -
                                     (gridSize.height - 1) / 2 + y};

                    if (!worldArea->IsValidCoordinate(xCoordinate, yCoordinate))
                    {
                        continue;
                    }

                    auto tl{worldArea->GetTile(xCoordinate, yCoordinate)};

                    auto objs_stack{tl->GetObjectsStack()};

                    auto objects{objs_stack->GetObjects()};

                    auto coord_nw{Point{xCoordinate, yCoordinate}};
                    auto coord_ne{Point{xCoordinate + 1, yCoordinate}};
                    auto coord_sw{Point{xCoordinate, yCoordinate + 1}};
                    auto coord_se{Point{xCoordinate + 1, yCoordinate + 1}};
                    auto coord_nee{Point{xCoordinate + 2, yCoordinate}};
                    auto coord_see{Point{xCoordinate + 2, yCoordinate + 1}};
                    auto coord_sese{Point{xCoordinate + 2, yCoordinate + 2}};
                    auto coord_ses{Point{xCoordinate + 1, yCoordinate + 2}};
                    auto coord_ss{Point{xCoordinate, yCoordinate + 2}};

                    if (!worldArea->IsValidCoordinate(coord_nw) ||
                        !worldArea->IsValidCoordinate(coord_ne) ||
                        !worldArea->IsValidCoordinate(coord_sw) ||
                        !worldArea->IsValidCoordinate(coord_se))
                    {
                        continue;
                    }

                    auto tl_nw{worldArea->GetTile(coord_nw)};
                    auto tl_ne{worldArea->GetTile(coord_ne)};
                    auto tl_sw{worldArea->GetTile(coord_sw)};
                    auto tl_se{worldArea->GetTile(coord_se)};
                    auto tl_nee{worldArea->GetTile(coord_nee)};
                    auto tl_see{worldArea->GetTile(coord_see)};
                    auto tl_sese{worldArea->GetTile(coord_sese)};
                    auto tl_ses{worldArea->GetTile(coord_ses)};
                    auto tl_ss{worldArea->GetTile(coord_ss)};

                    Vector<float> elevs;

                    auto elev_nw{tl_nw ? tl_nw->GetElevation() : 0.0f};
                    auto elev_ne{tl_ne ? tl_ne->GetElevation() : 0.0f};
                    auto elev_se{tl_se ? tl_se->GetElevation() : 0.0f};
                    auto elev_sw{tl_sw ? tl_sw->GetElevation() : 0.0f};
                    auto elev_nee{tl_nee ? tl_nee->GetElevation() : 0.0f};
                    auto elev_see{tl_see ? tl_see->GetElevation() : 0.0f};
                    auto elev_sese{tl_sese ? tl_sese->GetElevation() : 0.0f};
                    auto elev_ses{tl_ses ? tl_ses->GetElevation() : 0.0f};
                    auto elev_ss{tl_ss ? tl_ss->GetElevation() : 0.0f};

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

                    auto ground{tl->GetGround()};

                    if (ground == Hash("ground_water"))
                    {
                        auto anim_idx{
                            (GetTicks() + ((xCoordinate + yCoordinate) * 100)) /
                            500 % 3};
                        ground =
                            Hash("ground_water_" + std::to_string(anim_idx));
                    }

                    for (auto obj : objects)
                    {
                        auto obj_type{obj->GetType()};

                        if (obj_type == Hash("object_fir_tree") ||
                            obj_type == Hash("object_birch_tree"))
                        {
                            auto tree_obj{
                                std::static_pointer_cast<Forradia::TreeObject>(
                                    obj)};

                            auto trunk_parts{tree_obj->GetTrunkParts()};

                            auto needleTypes{tree_obj->GetNeedleTypes()};

                            auto w_factor{tree_obj->GetWidthFactor()};

                            for (auto i = 0; i < trunk_parts.size(); i++)
                            {
                                auto trunk_part{trunk_parts.at(i)};

                                auto needle_type{needleTypes.at(i)};

                                auto w_decr_factor{
                                    0.5f + (trunk_parts.size() - i) /
                                               CFloat(trunk_parts.size()) / 2};

                                auto tree_w{rendTileSize * w_factor *
                                            w_decr_factor};

                                auto trunk_part_x{trunk_part.x};
                                auto trunk_part_y{trunk_part.x};

                                trunk_part_x *=
                                    CFloat(i) / trunk_parts.size();

                                trunk_part_y *=
                                    CFloat(i) / trunk_parts.size();

                                auto trunk_part_x_center{
                                    (xCoordinate - 1) * rendTileSize -
                                    rendTileSize / 2 - trunk_part_x * tree_w};

                                auto trunk_part_y_center{
                                    (yCoordinate - 1) * rendTileSize -
                                    rendTileSize / 2 - trunk_part_y * tree_w};

                                auto trunk_part_z{trunk_part.y * rendTileSize};

                                auto trunk_part_width{rendTileSize * 0.2f *
                                                      w_decr_factor};

                                auto trunk_part_height{rendTileSize * 0.2f};

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

                                _<Engine::Renderers::ModelRenderer>().DrawModel(
                                    Hash(trunk_part_name),
                                    trunk_part_x_center - trunk_part_width / 2,
                                    trunk_part_y_center - trunk_part_width / 2,
                                    elev_avg - trunk_part_z, cameraPos,
                                    elevHeight);

                                auto needle_w{tree_w};

                                auto needle_h{rendTileSize};

                                if (needle_type)
                                {
                                    _<Engine::Renderers::ModelRenderer>()
                                        .DrawModel(needle_type,
                                                   trunk_part_x_center,
                                                   trunk_part_y_center,
                                                   elev_avg - trunk_part_z -
                                                       needle_h / 2,
                                                   cameraPos, elevHeight);
                                }
                            }
                        }
                        else
                        {
                            _<Engine::Renderers::ModelRenderer>().DrawModel(
                                obj_type,
                                (xCoordinate - 1) * rendTileSize -
                                    rendTileSize / 2,
                                (yCoordinate - 1) * rendTileSize -
                                    rendTileSize / 2,
                                elev_avg, cameraPos, elevHeight);
                        }
                    }

                    if (xCoordinate == worldAreaSize.width - playerPos.x &&
                        yCoordinate == worldAreaSize.height - playerPos.y)
                    {
                        _<Engine::Renderers::ModelRenderer>().DrawModel(
                            Hash("player"),
                            (xCoordinate - 1) * rendTileSize - rendTileSize / 2,
                            (yCoordinate - 1) * rendTileSize - rendTileSize / 2,
                            elev_avg, cameraPos, elevHeight);
                    }

                    _<Engine::Renderers::GroundRenderer>().DrawTile(
                        ground, xCoordinate - 1, yCoordinate - 1, rendTileSize,
                        cameraPos, elevs, elevHeight);
                }
            }
        }
    }
}
_NS_END_