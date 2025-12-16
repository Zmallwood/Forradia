/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "TimeUtilities.hpp"

namespace Forradia {
int GetTicks() {
  return SDL_GetTicks();
}
}