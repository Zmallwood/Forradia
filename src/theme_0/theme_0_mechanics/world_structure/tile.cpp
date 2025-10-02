/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "tile.hpp"
#include "objects_stack.hpp"

namespace forr {
  void tile::initialize() {
    m_objectsStack = std::make_shared<objects_stack>();
  }

  void tile::set_ground(str_view groundName) { m_ground = hash(groundName); }
}