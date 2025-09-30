/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia {
  void World::Initialize() {
    m_currentWorldArea = std::make_shared<WorldArea>();
  }
}