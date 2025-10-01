/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "get_loaded_images.hpp"
#include "../load_single_image.hpp"
#include "sub/construct_absolute_images_path.hpp"

namespace forr {
  Map<int, SharedPtr<SDL_Texture>>
  GetLoadedImages(StringView relativeImagesPath) {
    Map<int, SharedPtr<SDL_Texture>> imagesResult;
    auto imagesPath{ConstructAbsoluteImagesPath(relativeImagesPath)};
    if (!std::filesystem::exists(imagesPath)) {
      return imagesResult;
    }
    std::filesystem::recursive_directory_iterator rdi{imagesPath};
    for (auto it : rdi) {
      auto filePath{Replace(it.path().string(), '\\', '/')};
      if (GetFileExtension(filePath) == "png") {
        auto fileName{GetFileNameNoExtension(filePath)};
        auto hash{Hash(fileName)};
        auto image{LoadSingleImage(filePath)};
        imagesResult.insert({hash, image});
      }
    }
    return imagesResult;
  }
}