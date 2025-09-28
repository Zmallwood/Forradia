/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MouseUtilities.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

namespace Forradia
{
    PointF GetNormalizedMousePosition()
    {
        int xPx;
        int yPx;

        SDL_GetMouseState(&xPx, &yPx);

        auto canvasSize{GetCanvasSize()};

        return {CFloat(xPx) / canvasSize.width,
                CFloat(yPx) / canvasSize.height};
    }
}