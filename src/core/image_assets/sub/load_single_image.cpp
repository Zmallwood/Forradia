/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "load_single_image.hpp"
#include "core/sdl_device/sdl_device.hpp"

namespace forr {
  SharedPtr<SDL_Texture> LoadSingleImage(StringView path) {
    auto surface{SharedPtr<SDL_Surface>(IMG_Load(path.data()), SDLDeleter())};
    if (surface) {
      auto renderer{GetSingleton<SDLDevice>().GetRenderer().get()};
      auto texture{SharedPtr<SDL_Texture>(
          SDL_CreateTextureFromSurface(renderer, surface.get()), SDLDeleter())};
      return texture;
    }
    return nullptr;
  }
}