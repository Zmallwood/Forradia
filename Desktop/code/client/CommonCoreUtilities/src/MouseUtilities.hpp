/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Geometry/PointF.hpp"
#include <memory>

struct SDL_Window;

namespace Forradia
{
    /**
     * Obtain normalized mouse position.
     *
     * @param window Window to get the mouse position for.
     * @return The normalized mouse position.
     */
    auto GetNormalizedMousePosition(const std::shared_ptr<SDL_Window> &window) -> PointF;
}
