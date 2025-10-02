/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "world_view.hpp"
#include "core/images/image_bank.hpp"
#include "core/rend/images/image_renderer.hpp"
#include "theme_0/theme_0_mechanics/core_game_objects/player.hpp"
#include "theme_0/theme_0_mechanics/math/tile_grid_math.hpp"
#include "theme_0/theme_0_mechanics/world_interaction/tile_hovering.hpp"
#include "theme_0/theme_0_mechanics/world_structure/creature.hpp"
#include "theme_0/theme_0_mechanics/world_structure/object.hpp"
#include "theme_0/theme_0_mechanics/world_structure/objects_stack.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tree_object.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void world_view::render() const {
    auto grid_size{calculate_grid_size()};
    auto tile_size{calculate_tile_size()};
    auto player_position{get_singleton<player>().get_position()};
    auto world_area{get_singleton<world>().get_current_world_area()};
    auto player_elev{world_area->get_tile(player_position)->get_elevation()};
    auto extra_rows{8};
    for (auto i = 0; i < 3; i++) {
      for (auto y = -extra_rows; y < grid_size.h + extra_rows; y++) {
        for (auto x = 0; x < grid_size.w; x++) {
          auto x_coord{player_position.x - (grid_size.w - 1) / 2 + x};
          auto y_coord{player_position.y - (grid_size.h - 1) / 2 + y};
          if (!world_area->is_valid_coordinate(x_coord, y_coord)) {
            continue;
          }
          auto tile{world_area->get_tile(x_coord, y_coord)};
          float x_canvas;
          float y_canvas;
          float width_canvas;
          float height_canvas;
          auto coord_nw{point{x_coord, y_coord}};
          auto coord_ne{point{x_coord + 1, y_coord}};
          auto coord_sw{point{x_coord, y_coord + 1}};
          auto coord_se{point{x_coord + 1, y_coord + 1}};
          if (!world_area->is_valid_coordinate(coord_nw.x, coord_nw.y) ||
              !world_area->is_valid_coordinate(coord_ne.x, coord_ne.y) ||
              !world_area->is_valid_coordinate(coord_sw.x, coord_sw.y) ||
              !world_area->is_valid_coordinate(coord_se.x, coord_se.y)) {
            continue;
          }
          auto tile_nw{world_area->get_tile(coord_nw)};
          auto tile_ne{world_area->get_tile(coord_ne)};
          auto tile_sw{world_area->get_tile(coord_sw)};
          auto tile_se{world_area->get_tile(coord_se)};
          auto ground{tile ? tile->get_ground() : 0};
          auto ground_type_rendered{ground};
          x_canvas = x * tile_size.w;
          y_canvas =
              y * tile_size.h - tile_nw->get_elevation() * tile_size.h / 2;
          y_canvas += player_elev * tile_size.h / 2;
          width_canvas = tile_size.w;
          height_canvas = ceil(tile_size.h, 2.5f);
          // if (ground != Hash("GroundWater"))
          if (true) {
            str ground_name;
            if (ground == hash("GroundGrass")) {
              ground_name = "GroundGrass";
            } else if (ground == hash("GroundWater")) {
              ground_name = "GroundDirt";
            } else if (ground == hash("GroundDirt")) {
              ground_name = "GroundDirt";
            } else if (ground == hash("GroundRock")) {
              ground_name = "GroundRock";
            }
            str full_ground_name{ground_name};
            if (tile_nw->get_elevation() > tile_sw->get_elevation() &&
                tile_ne->get_elevation() > tile_se->get_elevation()) {
              height_canvas += tile_size.h / 2;
              full_ground_name = ground_name + "SlopeSouth";
            } else if (tile_nw->get_elevation() < tile_sw->get_elevation() &&
                       tile_ne->get_elevation() < tile_se->get_elevation()) {
              height_canvas -= tile_size.h / 2;
              full_ground_name = ground_name + "SlopeNorth";
            } else if (tile_ne->get_elevation() > tile_nw->get_elevation() &&
                       tile_se->get_elevation() > tile_sw->get_elevation()) {
              y_canvas -= tile_size.h / 2;
              height_canvas += tile_size.h / 2;
              full_ground_name = ground_name + "SlopeWest";
            } else if (tile_nw->get_elevation() > tile_ne->get_elevation() &&
                       tile_sw->get_elevation() > tile_se->get_elevation()) {
              height_canvas += tile_size.h / 2;
              full_ground_name = ground_name + "SlopeEast";
            } else if (tile_nw->get_elevation() > tile_ne->get_elevation() &&
                       tile_nw->get_elevation() > tile_se->get_elevation() &&
                       tile_nw->get_elevation() > tile_sw->get_elevation()) {
              height_canvas += tile_size.h / 2;
              full_ground_name = ground_name + "SlopeSouthEast";
            } else if (tile_ne->get_elevation() > tile_nw->get_elevation() &&
                       tile_ne->get_elevation() > tile_se->get_elevation() &&
                       tile_ne->get_elevation() > tile_sw->get_elevation()) {
              y_canvas -= tile_size.h / 2;
              height_canvas += tile_size.h / 2;
              full_ground_name = ground_name + "SlopeSouthWest";
            } else if (tile_sw->get_elevation() > tile_nw->get_elevation() &&
                       tile_sw->get_elevation() > tile_se->get_elevation() &&
                       tile_sw->get_elevation() > tile_ne->get_elevation()) {
              full_ground_name = ground_name + "SlopeNorthEast";
            } else if (tile_se->get_elevation() > tile_nw->get_elevation() &&
                       tile_se->get_elevation() > tile_ne->get_elevation() &&
                       tile_se->get_elevation() > tile_sw->get_elevation()) {
              full_ground_name = ground_name + "SlopeNorthWest";
            } else if (tile_sw->get_elevation() < tile_nw->get_elevation() &&
                       tile_sw->get_elevation() < tile_ne->get_elevation() &&
                       tile_sw->get_elevation() < tile_se->get_elevation()) {
              height_canvas += tile_size.h / 2;
              full_ground_name = ground_name + "SlopeSouthWestInverted";
            } else if (tile_se->get_elevation() < tile_nw->get_elevation() &&
                       tile_se->get_elevation() < tile_ne->get_elevation() &&
                       tile_se->get_elevation() < tile_sw->get_elevation()) {
              height_canvas += tile_size.h / 2;
              full_ground_name = ground_name + "SlopeSouthEastInverted";
            } else if (tile_nw->get_elevation() < tile_ne->get_elevation() &&
                       tile_nw->get_elevation() < tile_sw->get_elevation() &&
                       tile_nw->get_elevation() < tile_se->get_elevation()) {
              y_canvas -= tile_size.h / 2;
              full_ground_name = ground_name + "SlopeNorthWestInverted";
            } else if (tile_ne->get_elevation() < tile_nw->get_elevation() &&
                       tile_ne->get_elevation() < tile_sw->get_elevation() &&
                       tile_ne->get_elevation() < tile_se->get_elevation()) {
              full_ground_name = ground_name + "SlopeNorthEastInverted";
            } else if (tile_sw->get_elevation() == tile_ne->get_elevation() &&
                       tile_nw->get_elevation() < tile_sw->get_elevation() &&
                       tile_se->get_elevation() < tile_sw->get_elevation()) {
              y_canvas -= tile_size.h / 2;
              height_canvas += tile_size.h / 2;
              full_ground_name =
                  ground_name + "SlopeDiagonalSouthWestToNorthEast";
            } else if (tile_nw->get_elevation() == tile_se->get_elevation() &&
                       tile_ne->get_elevation() < tile_nw->get_elevation() &&
                       tile_sw->get_elevation() < tile_nw->get_elevation()) {
              height_canvas += tile_size.h / 2;
              full_ground_name =
                  ground_name + "SlopeDiagonalNorthWestToSouthEast";
            }
            // if (ground == Hash("GroundWater"))
            // {
            //     auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) *
            //     100)) / 500 % 3};
            //     fullGroundName = fullGroundName + "_" +
            //     std::to_string(animIndex);
            // }
            ground_type_rendered = hash(full_ground_name);
          }
          // else if (ground == Hash("GroundWater"))
          // {
          //     auto animIndex{(GetTicks() + ((xCoordinate + yCoordinate) *
          //     100)) / 500 % 3};
          //     groundTypeRendered = Hash("GroundWater_" +
          //     std::to_string(animIndex) + "_New");
          // }
          if (i == 0) {
            get_singleton<image_renderer>().draw_image(
                ground_type_rendered, x_canvas, y_canvas, width_canvas,
                height_canvas);
          } else if (ground != hash("GroundWater") && i == 1) {
            vec<directions> river_directions{tile->get_river_direction_1(),
                                             tile->get_river_direction_2()};
            auto river_part_width{0.4f * width_canvas};
            auto river_part_height{0.4f * height_canvas};
            auto part_length{2.5f};
            auto anim_index{(get_ticks() + ((x_coord + y_coord) * 100)) / 500 %
                            3};
            for (auto j = 0; j < 2; j++) {
              switch (river_directions.at(j)) {
              case directions::north: {
                for (auto k = 0.0f; k < part_length; k += 0.5f) {
                  rect_f bounds{
                      x_canvas + width_canvas / 2 - river_part_width / 2,
                      y_canvas + height_canvas / 2 - river_part_height / 2 -
                          k * river_part_height,
                      river_part_width, river_part_height};
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(anim_index), bounds.x,
                      bounds.y, bounds.w, bounds.h);
                }
              } break;
              case directions::east: {
                for (auto k = 0.0f; k < part_length; k += 0.5f) {
                  rect_f bounds{x_canvas + width_canvas / 2 -
                                    river_part_width / 2 + k * river_part_width,
                                y_canvas + height_canvas / 2 -
                                    river_part_height / 2,
                                river_part_width, river_part_height};
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(anim_index), bounds.x,
                      bounds.y, bounds.w, bounds.h);
                }
              } break;
              case directions::south: {
                for (auto k = 0.0f; k < part_length; k += 0.5f) {
                  rect_f bounds{
                      x_canvas + width_canvas / 2 - river_part_width / 2,
                      y_canvas + height_canvas / 2 + river_part_height / 2 +
                          k * river_part_height,
                      river_part_width, river_part_height};
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(anim_index), bounds.x,
                      bounds.y, bounds.w, bounds.h);
                }
              } break;
              case directions::west: {
                for (auto k = 0.0f; k < part_length; k += 0.5f) {
                  rect_f bounds{x_canvas + width_canvas / 2 -
                                    river_part_width / 2 - k * river_part_width,
                                y_canvas + height_canvas / 2 -
                                    river_part_height / 2,
                                river_part_width, river_part_height};
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(anim_index), bounds.x,
                      bounds.y, bounds.w, bounds.h);
                }
              } break;
              case directions::north_east: {
                for (auto k = 0.0f; k < part_length; k += 0.5f) {
                  rect_f bounds{x_canvas + width_canvas / 2 -
                                    river_part_width / 2 + k * river_part_width,
                                y_canvas + height_canvas / 2 -
                                    river_part_height / 2 -
                                    k * river_part_height,
                                river_part_width, river_part_height};
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(anim_index), bounds.x,
                      bounds.y, bounds.w, bounds.h);
                }
              } break;
              case directions::south_east: {
                for (auto k = 0.0f; k < part_length; k += 0.5f) {
                  rect_f bounds{x_canvas + width_canvas / 2 -
                                    river_part_width / 2 + k * river_part_width,
                                y_canvas + height_canvas / 2 -
                                    river_part_height / 2 +
                                    k * river_part_height,
                                river_part_width, river_part_height};
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(anim_index), bounds.x,
                      bounds.y, bounds.w, bounds.h);
                }
              } break;
              case directions::south_west: {
                for (auto k = 0.0f; k < part_length; k += 0.5f) {
                  rect_f bounds{x_canvas + width_canvas / 2 -
                                    river_part_width / 2 - k * river_part_width,
                                y_canvas + height_canvas / 2 -
                                    river_part_height / 2 +
                                    k * river_part_height,
                                river_part_width, river_part_height};
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(anim_index), bounds.x,
                      bounds.y, bounds.w, bounds.h);
                }
              } break;
              case directions::north_west: {
                for (auto k = 0.0f; k < part_length; k += 0.5f) {
                  rect_f bounds{x_canvas + width_canvas / 2 -
                                    river_part_width / 2 - k * river_part_width,
                                y_canvas + height_canvas / 2 -
                                    river_part_height / 2 -
                                    k * river_part_height,
                                river_part_width, river_part_height};
                  get_singleton<image_renderer>().draw_image(
                      "RiverPart_" + std::to_string(anim_index), bounds.x,
                      bounds.y, bounds.w, bounds.h);
                }
              } break;
              }
            }
          } else if (ground == hash("GroundWater") && i == 1) {
            auto anim_index{(get_ticks() + ((x_coord + y_coord) * 100)) / 500 %
                            3};
            get_singleton<image_renderer>().draw_image(
                "GroundWaterEdge", x_canvas - width_canvas * 0.2f,
                y_canvas - height_canvas * 0.2f, width_canvas * 1.4f,
                height_canvas * 1.4f);
          } else if (ground == hash("GroundWater") && i == 2) {

            auto anim_index{(get_ticks() + ((x_coord + y_coord) * 100)) / 500 %
                            3};
            get_singleton<image_renderer>().draw_image(
                "GroundWater_" + std::to_string(anim_index), x_canvas, y_canvas,
                width_canvas, height_canvas);

            for (auto i = 0; i < tile->get_elevation(); i++) {
              get_singleton<image_renderer>().draw_image(
                  "GroundWaterHeight", x_canvas, y_canvas, width_canvas,
                  height_canvas);
            }

            // groundTypeRendered = Hash("GroundWater_" +
            // std::to_string(animIndex) + "_New");
            // _<ImageRenderer>().DrawImage(groundTypeRendered, xCanvas -
            // tileSize.width * 3 / 2, yCanvas - tileSize.height * 3 / 2,
            // tileSize.width * 4, tileSize.height * 4);
            if (ground == hash("GroundWater")) {
              for (auto i = 0; i < tile->get_water_depth(); i++) {
                get_singleton<image_renderer>().draw_image(
                    "GroundWaterDepth", x_canvas, y_canvas, width_canvas,
                    height_canvas);
              }
            }
          }
          if (ground == hash("GroundGrass")) {
            get_singleton<image_renderer>().draw_image(
                "GroundGrassLayer", x_canvas, y_canvas, width_canvas,
                height_canvas);
          } else if (ground == hash("GroundDirt")) {
            get_singleton<image_renderer>().draw_image(
                "GroundDirtLayer", x_canvas, y_canvas, width_canvas,
                height_canvas);
          } else if (ground == hash("GroundRock")) {
            get_singleton<image_renderer>().draw_image(
                "GroundRockLayer", x_canvas, y_canvas, width_canvas,
                height_canvas);
          }
          if (i < 2) {
            continue;
          }
          // if (ground == Hash("GroundWater"))
          // {
          //     point N{xCoordinate, yCoordinate - 1};
          //     point S{xCoordinate, yCoordinate + 1};
          //     point W{xCoordinate - 1, yCoordinate};
          //     point E{xCoordinate + 1, yCoordinate};
          //     auto tileN{worldArea->IsValidCoordinate(N.x, N.y) ?
          //     worldArea->GetTile(N) : nullptr}; auto
          //     tileS{worldArea->IsValidCoordinate(S.x, S.y) ?
          //     worldArea->GetTile(S) : nullptr}; auto
          //     tileW{worldArea->IsValidCoordinate(W.x, W.y) ?
          //     worldArea->GetTile(W) : nullptr}; auto
          //     tileE{worldArea->IsValidCoordinate(E.x, E.y) ?
          //     worldArea->GetTile(E) : nullptr};
          //     if (tileN && tileN->GetGround() != Hash("GroundWater"))
          //     {
          //         _<ImageRenderer>().DrawImage("EdgeNorth", xCanvas, yCanvas,
          //         widthCanvas, heightCanvas);
          //     }
          //     if (tileE && tileE->GetGround() != Hash("GroundWater"))
          //     {
          //         _<ImageRenderer>().DrawImage("EdgeEast", xCanvas, yCanvas,
          //         widthCanvas, heightCanvas);
          //     }
          //     if (tileS && tileS->GetGround() != Hash("GroundWater"))
          //     {
          //         _<ImageRenderer>().DrawImage("EdgeSouth", xCanvas, yCanvas,
          //         widthCanvas, heightCanvas);
          //     }
          //     if (tileW && tileW->GetGround() != Hash("GroundWater"))
          //     {
          //         _<ImageRenderer>().DrawImage("EdgeWest", xCanvas, yCanvas,
          //         widthCanvas, heightCanvas);
          //     }
          // }
          auto hovered_coord{
              get_singleton<tile_hovering>().get_hovered_coordinate()};
          if (x_coord == hovered_coord.x && y_coord == hovered_coord.y) {
            get_singleton<image_renderer>().draw_image(
                "HoveredTile", x_canvas, y_canvas, width_canvas, height_canvas);
          }
          auto player_dest{get_singleton<player>().get_destination()};
          if (x_coord == player_dest.x && y_coord == player_dest.y) {
            get_singleton<image_renderer>().draw_image(
                "DestinationTile", x_canvas, y_canvas, width_canvas,
                height_canvas);
          }
          if (x_coord == player_position.x && y_coord == player_position.y) {
            get_singleton<image_renderer>().draw_image(
                "Shadow", x_canvas, y_canvas, width_canvas, height_canvas);
            get_singleton<image_renderer>().draw_image(
                "Player", x_canvas, y_canvas, tile_size.w, tile_size.h);
          }
          auto objects_stack{tile ? tile->get_objects_stack() : nullptr};
          if (objects_stack) {
            for (const auto &object : objects_stack->get_objects()) {
              if (object->get_type() != hash("ObjectPinkFlower")) {
                get_singleton<image_renderer>().draw_image(
                    "Shadow", x_canvas, y_canvas, tile_size.w, tile_size.h);
              }
              auto object_type{object->get_type()};
              if (object_type == hash("ObjectFirTree") ||
                  object_type == hash("ObjectBirchTree")) {
                auto tree_object{
                    std::static_pointer_cast<forr::tree_object>(object)};
                auto trunk_parts{tree_object->get_trunk_parts()};
                auto needleTypes{tree_object->get_needle_types()};
                auto width_factor{tree_object->get_width_factor()};
                for (auto i = 0; i < trunk_parts.size(); i++) {
                  auto trunk_part{trunk_parts.at(i)};
                  auto needle_type{needleTypes.at(i)};
                  auto width_decrease_factor{
                      0.5f + (trunk_parts.size() - i) /
                                 c_float(trunk_parts.size()) / 2};
                  auto tree_width{tile_size.w * width_factor *
                                  width_decrease_factor};
                  auto trunk_part_x{trunk_part.x};
                  trunk_part_x *=
                      c_float(i) / trunk_parts.size() *
                      std::sin(get_ticks() / 700.0f + x_coord * y_coord);
                  auto trunk_part_x_center{x_canvas + tile_size.w / 2 +
                                           trunk_part_x * tree_width};
                  auto trunk_part_y_center{y_canvas + tile_size.h -
                                           trunk_part.y * tile_size.h};
                  auto trunk_part_width{tile_size.w * 0.2f *
                                        width_decrease_factor};
                  auto trunk_part_height{tile_size.h * 0.2f};
                  str trunk_part_name;
                  if (object_type == hash("ObjectFirTree")) {
                    trunk_part_name = "ObjectFirTreeTrunkPart";
                  } else if (object_type == hash("ObjectBirchTree")) {
                    trunk_part_name = "ObjectBirchTreeTrunkPart";
                  }
                  get_singleton<image_renderer>().draw_image(
                      trunk_part_name,
                      trunk_part_x_center - trunk_part_width / 2,
                      trunk_part_y_center - trunk_part_height / 2,
                      trunk_part_width, trunk_part_height);
                  auto needle_width{tree_width};
                  auto needle_height{tile_size.h};
                  if (needle_type) {
                    get_singleton<image_renderer>().draw_image(
                        needle_type, trunk_part_x_center - needle_width / 2,
                        trunk_part_y_center - needle_height / 2, needle_width,
                        needle_height);
                  }
                }
                continue;
              }
              auto object_image_size{
                  get_singleton<image_bank>().get_image_size(object_type)};
              auto object_width{object_image_size.w / 60.0f * tile_size.w};
              auto object_height{object_image_size.h / 60.0f * tile_size.h};
              get_singleton<image_renderer>().draw_image(
                  object_type, x_canvas + tile_size.w / 2 - object_width / 2,
                  y_canvas + tile_size.h - object_height, object_width,
                  object_height);
            }
          }
          auto creature{tile ? tile->get_creature() : nullptr};
          if (creature) {
            auto creature_type{creature->get_type()};
            auto creature_image_size{
                get_singleton<image_bank>().get_image_size(creature_type)};
            auto creature_width{creature_image_size.w / 60.0f * tile_size.w};
            auto creature_height{creature_image_size.h / 60.0f * tile_size.h};
            get_singleton<image_renderer>().draw_image(
                creature_type, x_canvas + tile_size.w / 2 - creature_width / 2,
                y_canvas + tile_size.h - creature_height, creature_width,
                creature_height);
          }
        }
      }
    }
  }
}