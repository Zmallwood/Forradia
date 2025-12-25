/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "MouseUtilities.hpp"
    #include "CanvasUtilities.hpp"
    #include "ErrorUtilities.hpp"
    #include <SDL2/SDL.h>
// clang-format on

namespace ForradiaEngine
{
    auto getNormalizedMousePosition(const std::shared_ptr<SDL_Window> &window) -> PointF
    {
        { // Validation
            throwOnFalse(window != nullptr, "window is null");
        }

        int xPx;
        int yPx;

        SDL_GetMouseState(&xPx, &yPx);

        auto canvasSize{getCanvasSize(window)};

        return {static_cast<float>(xPx) / canvasSize.width,
                static_cast<float>(yPx) / canvasSize.height};
    }
}
