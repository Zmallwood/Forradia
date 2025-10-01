/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "body_part.hpp"
#include "body_part_types.hpp"

namespace forr {
  class player_body {
  public:
    player_body() { Initialize(); }

    body_part *GetBodyPartPtr(body_part_types bodyPartType);

  private:
    void Initialize();

    std::map<body_part_types, body_part> m_bodyParts;
  };
}