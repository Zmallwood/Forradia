/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_render_destination_rect.hpp"

namespace forr {
  SDL_Rect create_render_destination_rect(float x, float y, size textDimensions,
                                          bool centerAlign) {
    SDL_Rect rectResult;
    auto canvasSize{GetCanvasSize()};
    rectResult.x = CInt(x * canvasSize.width);
    rectResult.y = CInt(y * canvasSize.height);
    rectResult.w = textDimensions.width;
    rectResult.h = textDimensions.height;
    if (centerAlign) {
      rectResult.x -= rectResult.w / 2;
      rectResult.y -= rectResult.h / 2;
    }
    return rectResult;
  }
}