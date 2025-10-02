/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "draw_image.hpp"
#include "core/core.hpp"
#include "core/images/image_bank.hpp"

namespace forr {
  void draw_image(int image_name_hash, float x, float y, float width,
                  float height) {
    auto image{get_singleton<image_bank>().get_image(image_name_hash)};
    auto canvas_size{get_canvas_size()};
    auto x_px{c_int(x * canvas_size.w)};
    auto y_px{c_int(y * canvas_size.h)};
    auto width_px{c_int(width * canvas_size.w)};
    auto height_px{c_int(height * canvas_size.h)};
    SDL_Rect sdl_rect{x_px, y_px, width_px, height_px};
    SDL_RenderCopy(get_singleton<sdl_device>().get_renderer().get(),
                   image.get(), nullptr, &sdl_rect);
  }
}