/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "load_single_image.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  s_ptr<SDL_Texture> load_single_image(str_view path) {
    auto surface{s_ptr<SDL_Surface>(IMG_Load(path.data()), sdl_deleter())};
    if (surface) {
      auto renderer{get_singleton<sdl_device>().get_renderer().get()};
      auto texture{s_ptr<SDL_Texture>(
          SDL_CreateTextureFromSurface(renderer, surface.get()),
          sdl_deleter())};
      return texture;
    }
    return nullptr;
  }
}