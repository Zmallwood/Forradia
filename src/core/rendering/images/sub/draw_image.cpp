/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "draw_image.hpp"
#include "core/image_assets/image_bank.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  void draw_image(int imageNameHash, float x, float y, float width,
                  float height) {
    auto image{get_singleton<image_bank>().get_image(imageNameHash)};
    auto canvasSize{get_canvas_size()};
    auto xPx{c_int(x * canvasSize.width)};
    auto yPx{c_int(y * canvasSize.height)};
    auto widthPx{c_int(width * canvasSize.width)};
    auto heightPx{c_int(height * canvasSize.height)};
    SDL_Rect sdlRectangle{xPx, yPx, widthPx, heightPx};
    SDL_RenderCopy(get_singleton<sdl_device>().get_renderer().get(),
                   image.get(), nullptr, &sdlRectangle);
  }
}