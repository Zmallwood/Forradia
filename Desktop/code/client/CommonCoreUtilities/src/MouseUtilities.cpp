//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "MouseUtilities.hpp"
#include "CanvasUtilities.hpp"
#include "Functions.hpp"

namespace Forradia
{
    PointF GetNormallizedMousePosition(SharedPtr<SDL_Window> window)
    {
        // To hold the mouse position in pixels.

        int xPx;
        int yPx;

        // Get the mouse position.
        SDL_GetMouseState(&xPx, &yPx);

        // Get the size of the canvas.
        auto canvasSize{GetCanvasSize(window)};

        // Calculate the normalized mouse position.
        return {CFloat(xPx) / canvasSize.width, CFloat(yPx) / canvasSize.height};
    }
}