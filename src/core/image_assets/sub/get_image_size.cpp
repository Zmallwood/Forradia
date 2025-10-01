/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "get_image_size.hpp"

namespace forr {
  Size GetImageSize(s_ptr<SDL_Texture> texture) {
    Size size;
    if (texture) {
      SDL_QueryTexture(texture.get(), nullptr, nullptr, &size.width,
                       &size.height);
    }
    return size;
  }
}