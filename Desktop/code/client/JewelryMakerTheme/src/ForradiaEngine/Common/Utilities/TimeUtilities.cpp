/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "TimeUtilities.hpp"
    #include <SDL2/SDL.h>
// clang-format on

namespace ForradiaEngine
{
    auto getTicks() -> int
    {
        return SDL_GetTicks();
    }
}
