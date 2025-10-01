/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "construct_absolute_images_path.hpp"

namespace forr {
  String ConstructAbsoluteImagesPath(StringView relativeImagesPath) {
    auto basePath{String(SDL_GetBasePath())};
    auto imagesPath{basePath + relativeImagesPath.data()};
    return imagesPath;
  }
}