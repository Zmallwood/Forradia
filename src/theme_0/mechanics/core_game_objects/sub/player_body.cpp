/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "player_body.hpp"

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
}