/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MouseUtilities.hpp"
#include "CanvasUtilities.hpp"
#include "Functions.hpp"

namespace Forradia {
  auto GetNormallizedMousePosition(const std::shared_ptr<SDL_Window> &window) -> PointF {
    int xPx;
    int yPx;
    SDL_GetMouseState(&xPx, &yPx);
    auto canvasSize{GetCanvasSize(window)};
    return {static_cast<float>(xPx) / canvasSize.width,
            static_cast<float>(yPx) / canvasSize.height};
  }
}
