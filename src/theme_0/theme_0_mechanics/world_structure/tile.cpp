/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "tile.hpp"
#include "objects_stack.hpp"

namespace Forradia {
  void Tile::Initialize() { m_objectsStack = std::make_shared<ObjectsStack>(); }

  void Tile::SetGround(StringView groundName) { m_ground = Hash(groundName); }
}