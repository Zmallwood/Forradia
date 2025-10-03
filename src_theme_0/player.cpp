/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "player.hpp"
#include "game_props.hpp"
#include "world_struct.hpp"

namespace forr {
  void player_body::init() {
    m_parts.insert({body_part_types::overall_body, body_part()});
    m_parts.insert({body_part_types::right_arm, body_part()});
    m_parts.insert({body_part_types::left_arm, body_part()});
    m_parts.insert({body_part_types::legs, body_part()});
  }

  body_part *player_body::get_body_part_ptr(body_part_types type) {
    if (m_parts.contains(type)) {
      return &m_parts.at(type);
    }
    return nullptr;
  }

  void player::init() { move_to_suitable_pos(); }

  void player::move_to_suitable_pos() {
    auto w_area{_<world>().get_curr_w_area()};
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