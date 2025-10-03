/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gen_objs.hpp"
#include "theme_0/func/conf/game_props.hpp"
#include "theme_0/func/world_struct/objects_stack.hpp"
#include "theme_0/func/world_struct/tile.hpp"
#include "theme_0/func/world_struct/world.hpp"
#include "theme_0/func/world_struct/world_area.hpp"

namespace forr {
  void gen_objs() {
    auto w_area{_<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    auto scale{_<game_props>().k_world_scaling};
    auto num_fir_trees{1000 * scale + rand_int(50)};
    for (auto i = 0; i < num_fir_trees; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objs();
        tl->get_objects_stack()->add_tree_obj("ObjectFirTree");
      }
    }
    auto num_birch_trees{1000 * scale + rand_int(50)};
    for (auto i = 0; i < num_birch_trees; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objs();
        tl->get_objects_stack()->add_tree_obj("ObjectBirchTree");
      }
    }
    auto num_bush_1s{400 * scale + rand_int(100)};
    for (auto i = 0; i < num_bush_1s; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objs();
        tl->get_objects_stack()->add_obj("ObjectBush1");
      }
    }
    auto num_bush_2s{400 * scale + rand_int(100)};
    for (auto i = 0; i < num_bush_2s; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objs();
        tl->get_objects_stack()->add_obj("ObjectBush2");
      }
    }
    auto num_pink_flowers{400 * scale + rand_int(100)};
    for (auto i = 0; i < num_pink_flowers; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objs();
        tl->get_objects_stack()->add_obj("ObjectPinkFlower");
      }
    }
    auto num_tall_grasses{400 * scale + rand_int(100)};
    for (auto i = 0; i < num_tall_grasses; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objs();
        tl->get_objects_stack()->add_obj("ObjectTallGrass");
      }
    }
    auto num_stone_boulders{200 * scale + rand_int(100)};
    for (auto i = 0; i < num_stone_boulders; i++) {
      auto x{rand_int(sz.w)};
      auto y{rand_int(sz.h)};
      auto tl{w_area->get_tl(x, y)};
      if (tl && tl->get_water_depth() < 4) {
        tl->get_objects_stack()->clear_objs();
        tl->get_objects_stack()->add_obj("ObjectStoneBoulder");
      }
    }
  }
}