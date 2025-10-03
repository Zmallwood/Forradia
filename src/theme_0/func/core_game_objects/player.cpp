/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "player.hpp"
#include "theme_0/func/configuration/game_properties.hpp"
#include "theme_0/func/world_structure/tile.hpp"
#include "theme_0/func/world_structure/world.hpp"
#include "theme_0/func/world_structure/world_area.hpp"

namespace forr {
  void player::init() { move_to_suitable_pos(); }

  void player::move_to_suitable_pos() {
    auto w_area{get_ston<world>().get_curr_w_area()};
    auto sz{w_area->get_sz()};
    m_pos = {sz.w / 2, sz.h / 2};
    while (w_area->get_tl(m_pos)->get_ground() == hash("GroundWater")) {
      m_pos = {rand_int(sz.w), rand_int(sz.h)};
    }
  }

  void player::move_n() { m_pos.y -= 1; }

  void player::move_e() { m_pos.x += 1; }

  void player::move_s() { m_pos.y += 1; }

  void player::move_w() { m_pos.x -= 1; }
}