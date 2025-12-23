/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "MouseUtilities.hpp"
#include "CanvasUtilities.hpp"
#include "ErrorUtilities.hpp"
#include <SDL2/SDL.h>

namespace Forradia
{
    auto GetNormalizedMousePosition(const std::shared_ptr<SDL_Window> &window) -> PointF
    {
        ThrowOnFalse(window != nullptr, "window is null");

        int xPx;
        int yPx;
        SDL_GetMouseState(&xPx, &yPx);
        auto canvasSize{GetCanvasSize(window)};

        return {static_cast<float>(xPx) / canvasSize.width,
                static_cast<float>(yPx) / canvasSize.height};
    }
}
