/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "player_body.hpp"

namespace forr {
  void player_body::Initialize() {
    m_bodyParts.insert({body_part_types::OverallBody, body_part()});
    m_bodyParts.insert({body_part_types::RightArm, body_part()});
    m_bodyParts.insert({body_part_types::LeftArm, body_part()});
    m_bodyParts.insert({body_part_types::Legs, body_part()});
  }

  body_part *player_body::GetBodyPartPtr(body_part_types bodyPartType) {
    if (m_bodyParts.contains(bodyPartType)) {
      return &m_bodyParts.at(bodyPartType);
    }
    return nullptr;
  }
}