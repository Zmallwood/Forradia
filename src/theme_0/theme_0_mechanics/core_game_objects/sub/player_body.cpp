/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "player_body.hpp"

namespace forr {
  void player_body::initialize() {
    m_body_parts.insert({body_part_types::overall_body, body_part()});
    m_body_parts.insert({body_part_types::right_arm, body_part()});
    m_body_parts.insert({body_part_types::left_arm, body_part()});
    m_body_parts.insert({body_part_types::legs, body_part()});
  }

  body_part *player_body::get_body_part_ptr(body_part_types body_part_type) {
    if (m_body_parts.contains(body_part_type)) {
      return &m_body_parts.at(body_part_type);
    }
    return nullptr;
  }
}