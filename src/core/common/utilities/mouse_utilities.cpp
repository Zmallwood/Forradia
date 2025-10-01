/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "mouse_utilities.hpp"

namespace forr {
  point_f GetNormalizedMousePosition() {
    int xPx;
    int yPx;
    SDL_GetMouseState(&xPx, &yPx);
    auto canvasSize{GetCanvasSize()};
    return {CFloat(xPx) / canvasSize.width, CFloat(yPx) / canvasSize.height};
  }
}