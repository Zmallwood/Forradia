//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Geometry/PointF.hpp"
#include "Lang.hpp"

struct SDL_Window;

namespace Forradia
{
    ///
    /// Obtain normalized mouse position.
    ///
    /// @param window Window to get the mouse position for.
    /// @return The normalized mouse position.
    ///
    PointF GetNormallizedMousePosition(
        SharedPtr<SDL_Window> window);
}