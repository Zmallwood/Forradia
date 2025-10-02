/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_render_destination_rect.hpp"

namespace forr {
  SDL_Rect create_render_destination_rect(float x, float y,
                                          size text_dimensions,
                                          bool center_align) {
    SDL_Rect rect_result;
    auto canvas_size{get_canvas_size()};
    rect_result.x = c_int(x * canvas_size.w);
    rect_result.y = c_int(y * canvas_size.h);
    rect_result.w = text_dimensions.w;
    rect_result.h = text_dimensions.h;
    if (center_align) {
      rect_result.x -= rect_result.w / 2;
      rect_result.y -= rect_result.h / 2;
    }
    return rect_result;
  }
}