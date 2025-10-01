/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "creature.hpp"

namespace forr {
  void Creature::Initialize() { m_movementSpeed *= (RandomInt(3) + 1) / 2.0f; }
}