/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "construct_absolute_images_path.hpp"

namespace forr {
  str construct_absolute_images_path(str_view relativeImagesPath) {
    auto basePath{str(SDL_GetBasePath())};
    auto imagesPath{basePath + relativeImagesPath.data()};
    return imagesPath;
  }
}