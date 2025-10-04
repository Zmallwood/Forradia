/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_view.hpp"
#include "core.hpp"
#include "engine.hpp"
#include "rend.hpp"
#include "update.hpp"
#include "world_struct.hpp"

namespace forr {
  void world_view::render() const {
    auto grid_sz{calc_grid_sz()};
    auto tl_sz{calc_tl_sz()};
    auto player_pos{_<player>().pos()};
    auto w_area{_<world>().curr_w_area()};
    auto player_elev{w_area->get_tl(player_pos)->elev()};
    auto extra_rows{8};
    static float x_canv, y_canv, w_canv, h_canv;
    static int x_coord, y_coord;
    static int ground{0};
    static s_ptr<tile> tl, tl_nw, tl_sw, tl_ne, tl_se;
    static func<bool()> fn_draw_regular_ground{[&] {
      str ground_name;
      auto ground_type_rend{ground};
      if (ground == hash("GroundGrass"))
        ground_name = "GroundGrass";
      else if (ground == hash("GroundWater"))
        ground_name = "GroundDirt";
      else if (ground == hash("GroundDirt"))
        ground_name = "GroundDirt";
      else if (ground == hash("GroundRock"))
        ground_name = "GroundRock";
      str full_ground_name{ground_name};
      if (tl_nw->elev() > tl_sw->elev() && tl_ne->elev() > tl_se->elev()) {
        h_canv += tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeSouth";
      } else if (tl_nw->elev() < tl_sw->elev() &&
                 tl_ne->elev() < tl_se->elev()) {
        h_canv -= tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeNorth";
      } else if (tl_ne->elev() > tl_nw->elev() &&
                 tl_se->elev() > tl_sw->elev()) {
        y_canv -= tl_sz.h / 2;
        h_canv += tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeWest";
      } else if (tl_nw->elev() > tl_ne->elev() &&
                 tl_sw->elev() > tl_se->elev()) {
        h_canv += tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeEast";
      } else if (tl_nw->elev() > tl_ne->elev() &&
                 tl_nw->elev() > tl_se->elev() &&
                 tl_nw->elev() > tl_sw->elev()) {
        h_canv += tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeSouthEast";
      } else if (tl_ne->elev() > tl_nw->elev() &&
                 tl_ne->elev() > tl_se->elev() &&
                 tl_ne->elev() > tl_sw->elev()) {
        y_canv -= tl_sz.h / 2;
        h_canv += tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeSouthWest";
      } else if (tl_sw->elev() > tl_nw->elev() &&
                 tl_sw->elev() > tl_se->elev() &&
                 tl_sw->elev() > tl_ne->elev()) {
        full_ground_name = ground_name + "SlopeNorthEast";
      } else if (tl_se->elev() > tl_nw->elev() &&
                 tl_se->elev() > tl_ne->elev() &&
                 tl_se->elev() > tl_sw->elev()) {
        full_ground_name = ground_name + "SlopeNorthWest";
      } else if (tl_sw->elev() < tl_nw->elev() &&
                 tl_sw->elev() < tl_ne->elev() &&
                 tl_sw->elev() < tl_se->elev()) {
        h_canv += tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeSouthWestInverted";
      } else if (tl_se->elev() < tl_nw->elev() &&
                 tl_se->elev() < tl_ne->elev() &&
                 tl_se->elev() < tl_sw->elev()) {
        h_canv += tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeSouthEastInverted";
      } else if (tl_nw->elev() < tl_ne->elev() &&
                 tl_nw->elev() < tl_sw->elev() &&
                 tl_nw->elev() < tl_se->elev()) {
        y_canv -= tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeNorthWestInverted";
      } else if (tl_ne->elev() < tl_nw->elev() &&
                 tl_ne->elev() < tl_sw->elev() &&
                 tl_ne->elev() < tl_se->elev()) {
        full_ground_name = ground_name + "SlopeNorthEastInverted";
      } else if (tl_sw->elev() == tl_ne->elev() &&
                 tl_nw->elev() < tl_sw->elev() &&
                 tl_se->elev() < tl_sw->elev()) {
        y_canv -= tl_sz.h / 2;
        h_canv += tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeDiagonalSouthWestToNorthEast";
      } else if (tl_nw->elev() == tl_se->elev() &&
                 tl_ne->elev() < tl_nw->elev() &&
                 tl_sw->elev() < tl_nw->elev()) {
        h_canv += tl_sz.h / 2;
        full_ground_name = ground_name + "SlopeDiagonalNorthWestToSouthEast";
      }
      ground_type_rend = hash(full_ground_name);
      _<image_rend>().draw_img(ground_type_rend, x_canv, y_canv, w_canv,
                               h_canv);
      return true;
    }};
    static func<void()> fn_draw_rivers{[] {
      vec<dirs> river_dirs{tl->river_dir_1(), tl->river_dir_2()};
      auto river_part_w{0.4f * w_canv};
      auto river_part_h{0.4f * h_canv};
      auto part_len{2.5f};
      auto anim_idx{(ticks() + ((x_coord + y_coord) * 100)) / 500 % 3};
      for (auto j = 0; j < 2; j++) {
        switch (river_dirs.at(j)) {
        case dirs::n:
          for (auto k = 0.0f; k < part_len; k += 0.5f) {
            rect_f b{x_canv + w_canv / 2 - river_part_w / 2,
                     y_canv + h_canv / 2 - river_part_h / 2 - k * river_part_h,
                     river_part_w, river_part_h};
            _<image_rend>().draw_img("RiverPart_" + std::to_string(anim_idx),
                                     b.x, b.y, b.w, b.h);
          }
          break;
        case dirs::e:
          for (auto k = 0.0f; k < part_len; k += 0.5f) {
            rect_f b{x_canv + w_canv / 2 - river_part_w / 2 + k * river_part_w,
                     y_canv + h_canv / 2 - river_part_h / 2, river_part_w,
                     river_part_h};
            _<image_rend>().draw_img("RiverPart_" + std::to_string(anim_idx),
                                     b.x, b.y, b.w, b.h);
          }
          break;
        case dirs::s:
          for (auto k = 0.0f; k < part_len; k += 0.5f) {
            rect_f b{x_canv + w_canv / 2 - river_part_w / 2,
                     y_canv + h_canv / 2 + river_part_h / 2 + k * river_part_h,
                     river_part_w, river_part_h};
            _<image_rend>().draw_img("RiverPart_" + std::to_string(anim_idx),
                                     b.x, b.y, b.w, b.h);
          }
          break;
        case dirs::w:
          for (auto k = 0.0f; k < part_len; k += 0.5f) {
            rect_f b{x_canv + w_canv / 2 - river_part_w / 2 - k * river_part_w,
                     y_canv + h_canv / 2 - river_part_h / 2, river_part_w,
                     river_part_h};
            _<image_rend>().draw_img("RiverPart_" + std::to_string(anim_idx),
                                     b.x, b.y, b.w, b.h);
          }
          break;
        case dirs::ne:
          for (auto k = 0.0f; k < part_len; k += 0.5f) {
            rect_f b{x_canv + w_canv / 2 - river_part_w / 2 + k * river_part_w,
                     y_canv + h_canv / 2 - river_part_h / 2 - k * river_part_h,
                     river_part_w, river_part_h};
            _<image_rend>().draw_img("RiverPart_" + std::to_string(anim_idx),
                                     b.x, b.y, b.w, b.h);
          }
          break;
        case dirs::se:
          for (auto k = 0.0f; k < part_len; k += 0.5f) {
            rect_f b{x_canv + w_canv / 2 - river_part_w / 2 + k * river_part_w,
                     y_canv + h_canv / 2 - river_part_h / 2 + k * river_part_h,
                     river_part_w, river_part_h};
            _<image_rend>().draw_img("RiverPart_" + std::to_string(anim_idx),
                                     b.x, b.y, b.w, b.h);
          }
          break;
        case dirs::sw:
          for (auto k = 0.0f; k < part_len; k += 0.5f) {
            rect_f b{x_canv + w_canv / 2 - river_part_w / 2 - k * river_part_w,
                     y_canv + h_canv / 2 - river_part_h / 2 + k * river_part_h,
                     river_part_w, river_part_h};
            _<image_rend>().draw_img("RiverPart_" + std::to_string(anim_idx),
                                     b.x, b.y, b.w, b.h);
          }
          break;
        case dirs::nw:
          for (auto k = 0.0f; k < part_len; k += 0.5f) {
            rect_f b{x_canv + w_canv / 2 - river_part_w / 2 - k * river_part_w,
                     y_canv + h_canv / 2 - river_part_h / 2 - k * river_part_h,
                     river_part_w, river_part_h};
            _<image_rend>().draw_img("RiverPart_" + std::to_string(anim_idx),
                                     b.x, b.y, b.w, b.h);
          }
          break;
        }
      }
    }};
    static func<void()> fn_draw_water_edges{[] {
      _<image_rend>().draw_img("GroundWaterEdge", x_canv - w_canv * 0.2f,
                               y_canv - h_canv * 0.2f, w_canv * 1.4f,
                               h_canv * 1.4f);
    }};
    static func<void()> fn_draw_water{[] {
      auto anim_idx{(ticks() + ((x_coord + y_coord) * 100)) / 500 % 3};
      _<image_rend>().draw_img("GroundWater_" + std::to_string(anim_idx),
                               x_canv, y_canv, w_canv, h_canv);

      for (auto i = 0; i < tl->elev(); i++)
        _<image_rend>().draw_img("GroundWaterHeight", x_canv, y_canv, w_canv,
                                 h_canv);
      for (auto i = 0; i < tl->water_depth(); i++)
        _<image_rend>().draw_img("GroundWaterDepth", x_canv, y_canv, w_canv,
                                 h_canv);
    }};
    static func<void()> fn_draw_layers{[] {
      if (ground == hash("GroundGrass"))
        _<image_rend>().draw_img("GroundGrassLayer", x_canv, y_canv, w_canv,
                                 h_canv);
      else if (ground == hash("GroundDirt"))
        _<image_rend>().draw_img("GroundDirtLayer", x_canv, y_canv, w_canv,
                                 h_canv);
      else if (ground == hash("GroundRock"))
        _<image_rend>().draw_img("GroundRockLayer", x_canv, y_canv, w_canv,
                                 h_canv);
    }};
    static func<void()> fn_draw_tile_symbols{[] {
      auto hovered_coord{_<tl_hovering>().hovered_coord()};
      if (x_coord == hovered_coord.x && y_coord == hovered_coord.y)
        _<image_rend>().draw_img("HoveredTile", x_canv, y_canv, w_canv, h_canv);
      auto player_dest{_<player>().dest()};
      if (x_coord == player_dest.x && y_coord == player_dest.y)
        _<image_rend>().draw_img("DestinationTile", x_canv, y_canv, w_canv,
                                 h_canv);
    }};
    static func<void()> fn_draw_player{[&] {
      if (x_coord == player_pos.x && y_coord == player_pos.y) {
        _<image_rend>().draw_img("Shadow", x_canv, y_canv, w_canv, h_canv);
        _<image_rend>().draw_img("Player", x_canv, y_canv, tl_sz.w, tl_sz.h);
      }
    }};
    static func<void()> fn_draw_objects{[&] {
      auto objs_stack{tl ? tl->objects_stack() : nullptr};
      if (objs_stack) {
        for (const auto &obj : objs_stack->objects()) {
          if (obj->type() != hash("ObjectPinkFlower"))
            _<image_rend>().draw_img("Shadow", x_canv, y_canv, tl_sz.w,
                                     tl_sz.h);
          auto obj_type{obj->type()};
          if (obj_type == hash("ObjectFirTree") ||
              obj_type == hash("ObjectBirchTree")) {
            auto tree_obj{std::static_pointer_cast<forr::tree_object>(obj)};
            auto trunk_parts{tree_obj->trunk_parts()};
            auto needleTypes{tree_obj->needle_types()};
            auto w_factor{tree_obj->w_factor()};
            for (auto i = 0; i < trunk_parts.size(); i++) {
              auto trunk_part{trunk_parts.at(i)};
              auto needle_type{needleTypes.at(i)};
              auto w_decr_factor{0.5f + (trunk_parts.size() - i) /
                                            c_float(trunk_parts.size()) / 2};
              auto tree_w{tl_sz.w * w_factor * w_decr_factor};
              auto trunk_part_x{trunk_part.x};
              trunk_part_x *= c_float(i) / trunk_parts.size() *
                              std::sin(ticks() / 700.0f + x_coord * y_coord);
              auto trunk_part_x_center{x_canv + tl_sz.w / 2 +
                                       trunk_part_x * tree_w};
              auto trunk_part_y_center{y_canv + tl_sz.h -
                                       trunk_part.y * tl_sz.h};
              auto trunk_part_width{tl_sz.w * 0.2f * w_decr_factor};
              auto trunk_part_height{tl_sz.h * 0.2f};
              str trunk_part_name;
              if (obj_type == hash("ObjectFirTree"))
                trunk_part_name = "ObjectFirTreeTrunkPart";
              else if (obj_type == hash("ObjectBirchTree"))
                trunk_part_name = "ObjectBirchTreeTrunkPart";
              _<image_rend>().draw_img(
                  trunk_part_name, trunk_part_x_center - trunk_part_width / 2,
                  trunk_part_y_center - trunk_part_height / 2, trunk_part_width,
                  trunk_part_height);
              auto needle_w{tree_w};
              auto needle_h{tl_sz.h};
              if (needle_type)
                _<image_rend>().draw_img(
                    needle_type, trunk_part_x_center - needle_w / 2,
                    trunk_part_y_center - needle_h / 2, needle_w, needle_h);
            }
            continue;
          }
          auto obj_img_sz{_<image_bank>().get_img_sz(obj_type)};
          auto obj_w{obj_img_sz.w / 60.0f * tl_sz.w};
          auto obj_h{obj_img_sz.h / 60.0f * tl_sz.h};
          _<image_rend>().draw_img(obj_type, x_canv + tl_sz.w / 2 - obj_w / 2,
                                   y_canv + tl_sz.h - obj_h, obj_w, obj_h);
        }
      }
    }};
    static func<void()> fn_draw_creature{[&] {
      auto crea{tl ? tl->creature() : nullptr};
      if (crea) {
        auto crea_type{crea->type()};
        auto crea_img_sz{_<image_bank>().get_img_sz(crea_type)};
        auto crea_w{crea_img_sz.w / 60.0f * tl_sz.w};
        auto crea_h{crea_img_sz.h / 60.0f * tl_sz.h};
        _<image_rend>().draw_img(crea_type, x_canv + tl_sz.w / 2 - crea_w / 2,
                                 y_canv + tl_sz.h - crea_h, crea_w, crea_h);
      }
    }};
    static func<void()> fn_draw_npc{[&] {
      auto npc{tl ? tl->npc() : nullptr};
      if (npc) {
        auto npc_type{npc->type()};
        auto npc_img_sz{_<image_bank>().get_img_sz(npc_type)};
        auto npc_w{npc_img_sz.w / 60.0f * tl_sz.w};
        auto npc_h{npc_img_sz.h / 60.0f * tl_sz.h};
        _<image_rend>().draw_img(npc_type, x_canv + tl_sz.w / 2 - npc_w / 2,
                                 y_canv + tl_sz.h - npc_h, npc_w, npc_h);
      }
    }};
    {
      for (auto i = 0; i < 3; i++) {
        for (auto y = -extra_rows; y < grid_sz.h + extra_rows; y++) {
          for (auto x = 0; x < grid_sz.w; x++) {
            x_coord = player_pos.x - (grid_sz.w - 1) / 2 + x;
            y_coord = player_pos.y - (grid_sz.h - 1) / 2 + y;
            if (!w_area->is_valid_coord(x_coord, y_coord))
              continue;
            tl = w_area->get_tl(x_coord, y_coord);
            auto coord_nw{pt{x_coord, y_coord}};
            auto coord_ne{pt{x_coord + 1, y_coord}};
            auto coord_sw{pt{x_coord, y_coord + 1}};
            auto coord_se{pt{x_coord + 1, y_coord + 1}};
            if (!w_area->is_valid_coord(coord_nw) ||
                !w_area->is_valid_coord(coord_ne) ||
                !w_area->is_valid_coord(coord_sw) ||
                !w_area->is_valid_coord(coord_se))
              continue;
            tl_nw = w_area->get_tl(coord_nw);
            tl_ne = w_area->get_tl(coord_ne);
            tl_sw = w_area->get_tl(coord_sw);
            tl_se = w_area->get_tl(coord_se);
            ground = tl ? tl->ground() : 0;
            x_canv = x * tl_sz.w;
            y_canv = y * tl_sz.h - tl_nw->elev() * tl_sz.h / 2;
            y_canv += player_elev * tl_sz.h / 2;
            w_canv = tl_sz.w;
            h_canv = ceil(tl_sz.h, 2.5f);
            if (i == 0 && !fn_draw_regular_ground())
              continue;
            else if (i == 1 && ground != hash("GroundWater") && i == 1)
              fn_draw_rivers();
            else if (i == 1 && ground == hash("GroundWater") && i == 1)
              fn_draw_water_edges();
            else if (i == 1 && ground == hash("GroundWater") && i == 2)
              fn_draw_water();
            if (i == 1)
              fn_draw_layers();
            if (i < 2)
              continue;
            fn_draw_tile_symbols();
            fn_draw_player();
            fn_draw_objects();
            fn_draw_creature();
            fn_draw_npc();
          }
        }
      }
    }
  }
}