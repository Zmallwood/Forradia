/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_render_destination_rect.hpp"

namespace forr {
  SDL_Rect create_render_destination_rect(float x, float y, size text_dim,
                                          bool cent_align) {
    SDL_Rect rect_res;
    auto canv_sz{get_canvas_size()};
    rect_res.x = c_int(x * canv_sz.w);
    rect_res.y = c_int(y * canv_sz.h);
    rect_res.w = text_dim.w;
    rect_res.h = text_dim.h;
    if (cent_align) {
      rect_res.x -= rect_res.w / 2;
      rect_res.y -= rect_res.h / 2;
    }
    return rect_res;
  }
}