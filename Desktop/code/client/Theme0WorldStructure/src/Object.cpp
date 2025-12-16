/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Object.hpp"

namespace Forradia::Theme0 {
void Object::Initialize() {
  // Randomize the model scaling between 0.25f and 2.0f using integer steps.
  m_modelScaling = 0.5f + static_cast<float>(GetRandomInt(100)) / 100.0f;
}
}