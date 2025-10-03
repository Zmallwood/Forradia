/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "player.hpp"
#include "theme_0/mechanics/configuration/game_properties.hpp"
#include "theme_0/mechanics/world_structure/tile.hpp"
#include "theme_0/mechanics/world_structure/world.hpp"
#include "theme_0/mechanics/world_structure/world_area.hpp"

namespace forr {
  void player::initialize() { move_to_suitable_position(); }

  void player::move_to_suitable_position() {
    auto w_area{get_singleton<world>().get_current_world_area()};
    auto sz{w_area->get_size()};
    m_pos = {sz.w / 2, sz.h / 2};
    while (w_area->get_tile(m_pos)->get_ground() == hash("GroundWater")) {
      m_pos = {random_int(sz.w), random_int(sz.h)};
    }
  }

  void player::move_north() { m_pos.y -= 1; }

  void player::move_east() { m_pos.x += 1; }

  void player::move_south() { m_pos.y += 1; }

  void player::move_west() { m_pos.x -= 1; }
}