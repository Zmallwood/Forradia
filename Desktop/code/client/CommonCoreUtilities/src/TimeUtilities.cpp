/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "TimeUtilities.hpp"
#include "StdAfx.hpp"

namespace Forradia {
  auto GetTicks() -> int {
    return SDL_GetTicks();
  }
}
