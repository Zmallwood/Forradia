/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "RandomizeUtilities.hpp"

namespace Forradia {
  void Randomize() { srand(time(nullptr)); }

  int RandomInt(int upperLimit) { return rand() % upperLimit; }
}
