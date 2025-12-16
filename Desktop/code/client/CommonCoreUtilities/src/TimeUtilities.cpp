//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "TimeUtilities.hpp"

namespace Forradia {
    int GetTicks() {
        // Get the number of ticks.
        return SDL_GetTicks();
    }
}