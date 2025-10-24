//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Lang.hpp"
#include "Geometry/PointF.hpp"

struct SDL_Window;

namespace Forradia
{
    PointF GetNormallizedMousePosition(
        SharedPtr<SDL_Window> window);
}