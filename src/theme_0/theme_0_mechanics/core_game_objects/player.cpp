/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "player.hpp"
#include "theme_0/theme_0_mechanics/configuration/game_properties.hpp"
#include "theme_0/theme_0_mechanics/world_structure/tile.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world.hpp"
#include "theme_0/theme_0_mechanics/world_structure/world_area.hpp"

namespace forr {
  void player::initialize() { move_to_suitable_position(); }

  void player::move_to_suitable_position() {
    auto worldArea{get_singleton<world>().get_current_world_area()};
    auto size{worldArea->get_size()};
    m_position = {size.width / 2, size.height / 2};
    while (worldArea->get_tile(m_position)->get_ground() ==
           hash("GroundWater")) {
      m_position = {random_int(size.width), random_int(size.height)};
    }
  }

  void player::move_north() { m_position.y -= 1; }

  void player::move_east() { m_position.x += 1; }

  void player::move_south() { m_position.y += 1; }

  void player::move_west() { m_position.x -= 1; }
}