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

namespace Forradia {
PointF GetNormallizedMousePosition(SharedPtr<SDL_Window> window) {
  int xPx;
  int yPx;
  SDL_GetMouseState(&xPx, &yPx);
  auto canvasSize{GetCanvasSize(window)};
  return {CFloat(xPx) / canvasSize.width, CFloat(yPx) / canvasSize.height};
}
}