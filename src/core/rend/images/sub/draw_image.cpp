/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "draw_image.hpp"
#include "core/core.hpp"

namespace forr {
  void draw_image(int img_name_hash, float x, float y, float w, float h) {
    auto img{get_singleton<image_bank>().get_image(img_name_hash)};
    auto canv_sz{get_canvas_size()};
    auto x_px{c_int(x * canv_sz.w)};
    auto y_px{c_int(y * canv_sz.h)};
    auto w_px{c_int(w * canv_sz.w)};
    auto h_px{c_int(h * canv_sz.h)};
    SDL_Rect sdl_rect{x_px, y_px, w_px, h_px};
    SDL_RenderCopy(get_singleton<sdl_device>().get_renderer().get(), img.get(),
                   nullptr, &sdl_rect);
  }
}