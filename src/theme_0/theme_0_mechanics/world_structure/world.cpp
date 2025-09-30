/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "world.hpp"
#include "world_area.hpp"

namespace Forradia {
  void World::Initialize() {
    m_currentWorldArea = std::make_shared<WorldArea>();
  }
}