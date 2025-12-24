/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "TimeUtilities.hpp"
#include <SDL2/SDL.h>

namespace Forradia
{
    auto getTicks() -> int
    {
        return SDL_GetTicks();
    }
}
