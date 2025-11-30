//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TimeUtilities.hpp"

namespace AAK
{
    namespace Forradia
    {
        int GetTicks()
        {
            // Get the number of ticks.

            return SDL_GetTicks();
        }
    }
}