//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "MouseUtilities.hpp"
#include "CanvasUtilities.hpp"

namespace Forradia
{
    PointF GetNormallizedMousePosition(
        SharedPtr<SDL_Window> window)
    {
        int xPx;
        int yPx;

        // Get the mouse position.

        SDL_GetMouseState(&xPx, &yPx);
        auto canvasSize{GetCanvasSize(window)};

        // Calculate the normalized mouse position.
        
        return {CFloat(xPx) / canvasSize.width,
                CFloat(yPx) / canvasSize.height};
    }
}