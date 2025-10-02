/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "generate_objects.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/objects_stack.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void generate_objects() {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto size{worldArea->get_size()};
    auto scale{get_singleton<game_properties>().k_worldScalingFactor};
    auto numFirTrees{1000 * scale + random_int(50)};
    for (auto i = 0; i < numFirTrees; i++) {
      auto x{random_int(size.width)};
      auto y{random_int(size.height)};
      auto tile{worldArea->get_tile(x, y)};
      if (tile && tile->get_ground() != hash("GroundWater") &&
          tile->get_ground() != hash("GroundRock")) {
        tile->get_objects_stack()->clear_objects();
        tile->get_objects_stack()->add_tree_object("ObjectFirTree");
      }
    }
    auto numBirchTrees{1000 * scale + random_int(50)};
    for (auto i = 0; i < numBirchTrees; i++) {
      auto x{random_int(size.width)};
      auto y{random_int(size.height)};
      auto tile{worldArea->get_tile(x, y)};
      if (tile && tile->get_ground() != hash("GroundWater") &&
          tile->get_ground() != hash("GroundRock")) {
        tile->get_objects_stack()->clear_objects();
        tile->get_objects_stack()->add_tree_object("ObjectBirchTree");
      }
    }
    auto numBush1s{400 * scale + random_int(100)};
    for (auto i = 0; i < numBush1s; i++) {
      auto x{random_int(size.width)};
      auto y{random_int(size.height)};
      auto tile{worldArea->get_tile(x, y)};
      if (tile && tile->get_ground() != hash("GroundWater") &&
          tile->get_ground() != hash("GroundRock")) {
        tile->get_objects_stack()->clear_objects();
        tile->get_objects_stack()->add_object("ObjectBush1");
      }
    }
    auto numBush2s{400 * scale + random_int(100)};
    for (auto i = 0; i < numBush2s; i++) {
      auto x{random_int(size.width)};
      auto y{random_int(size.height)};
      auto tile{worldArea->get_tile(x, y)};
      if (tile && tile->get_ground() != hash("GroundWater") &&
          tile->get_ground() != hash("GroundRock")) {
        tile->get_objects_stack()->clear_objects();
        tile->get_objects_stack()->add_object("ObjectBush2");
      }
    }
    auto numPinkFlowers{400 * scale + random_int(100)};
    for (auto i = 0; i < numPinkFlowers; i++) {
      auto x{random_int(size.width)};
      auto y{random_int(size.height)};
      auto tile{worldArea->get_tile(x, y)};
      if (tile && tile->get_ground() != hash("GroundWater") &&
          tile->get_ground() != hash("GroundRock")) {
        tile->get_objects_stack()->clear_objects();
        tile->get_objects_stack()->add_object("ObjectPinkFlower");
      }
    }
    auto numTallGrasses{400 * scale + random_int(100)};
    for (auto i = 0; i < numTallGrasses; i++) {
      auto x{random_int(size.width)};
      auto y{random_int(size.height)};
      auto tile{worldArea->get_tile(x, y)};
      if (tile && tile->get_ground() != hash("GroundWater") &&
          tile->get_ground() != hash("GroundRock")) {
        tile->get_objects_stack()->clear_objects();
        tile->get_objects_stack()->add_object("ObjectTallGrass");
      }
    }
    auto numStoneBoulders{200 * scale + random_int(100)};
    for (auto i = 0; i < numStoneBoulders; i++) {
      auto x{random_int(size.width)};
      auto y{random_int(size.height)};
      auto tile{worldArea->get_tile(x, y)};
      if (tile && tile->get_water_depth() < 4) {
        tile->get_objects_stack()->clear_objects();
        tile->get_objects_stack()->add_object("ObjectStoneBoulder");
      }
    }
  }
}