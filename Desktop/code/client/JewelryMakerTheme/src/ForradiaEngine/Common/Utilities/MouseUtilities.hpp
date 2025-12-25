/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Matter/Geometry/PointF.hpp"
    #include <memory>
// clang-format on

struct SDL_Window;

namespace ForradiaEngine
{
    /**
     *  Obtain normalized mouse position.
     *
     *  @param window Window to get the mouse position for.
     *  @return The normalized mouse position.
     */
    auto getNormalizedMousePosition(const std::shared_ptr<SDL_Window> &window) -> PointF;
}
