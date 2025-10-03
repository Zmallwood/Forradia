/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_objects.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/objects_stack.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_objects() {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto sz{w_area->get_size()};
    auto scale{get_singleton<game_properties>().k_world_scaling};
    auto num_fir_trees{1000 * scale + random_int(50)};
    for (auto i = 0; i < num_fir_trees; i++) {
      auto x{random_int(sz.w)};
      auto y{random_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objects();
        tl->get_objects_stack()->add_tree_object("ObjectFirTree");
      }
    }
    auto num_birch_trees{1000 * scale + random_int(50)};
    for (auto i = 0; i < num_birch_trees; i++) {
      auto x{random_int(sz.w)};
      auto y{random_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objects();
        tl->get_objects_stack()->add_tree_object("ObjectBirchTree");
      }
    }
    auto num_bush_1s{400 * scale + random_int(100)};
    for (auto i = 0; i < num_bush_1s; i++) {
      auto x{random_int(sz.w)};
      auto y{random_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objects();
        tl->get_objects_stack()->add_object("ObjectBush1");
      }
    }
    auto num_bush_2s{400 * scale + random_int(100)};
    for (auto i = 0; i < num_bush_2s; i++) {
      auto x{random_int(sz.w)};
      auto y{random_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objects();
        tl->get_objects_stack()->add_object("ObjectBush2");
      }
    }
    auto num_pink_flowers{400 * scale + random_int(100)};
    for (auto i = 0; i < num_pink_flowers; i++) {
      auto x{random_int(sz.w)};
      auto y{random_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objects();
        tl->get_objects_stack()->add_object("ObjectPinkFlower");
      }
    }
    auto num_tall_grasses{400 * scale + random_int(100)};
    for (auto i = 0; i < num_tall_grasses; i++) {
      auto x{random_int(sz.w)};
      auto y{random_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && tl->get_ground() != hash("GroundWater") &&
          tl->get_ground() != hash("GroundRock")) {
        tl->get_objects_stack()->clear_objects();
        tl->get_objects_stack()->add_object("ObjectTallGrass");
      }
    }
    auto num_stone_boulders{200 * scale + random_int(100)};
    for (auto i = 0; i < num_stone_boulders; i++) {
      auto x{random_int(sz.w)};
      auto y{random_int(sz.h)};
      auto tl{w_area->get_tile(x, y)};
      if (tl && tl->get_water_depth() < 4) {
        tl->get_objects_stack()->clear_objects();
        tl->get_objects_stack()->add_object("ObjectStoneBoulder");
      }
    }
  }
}