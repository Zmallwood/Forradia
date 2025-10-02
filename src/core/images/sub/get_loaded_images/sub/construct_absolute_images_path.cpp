/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "construct_absolute_images_path.hpp"

namespace forr {
  str construct_absolute_images_path(str_view relatives_images_path) {
    auto base_path{str(SDL_GetBasePath())};
    auto images_path{base_path + relatives_images_path.data()};
    return images_path;
  }
}