/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "get_loaded_images.hpp"
#include "../load_single_image.hpp"
#include "sub/construct_absolute_images_path.hpp"

namespace forr {
  std::map<int, s_ptr<SDL_Texture>>
  get_loaded_images(str_view relativeImagesPath) {
    std::map<int, s_ptr<SDL_Texture>> imagesResult;
    auto imagesPath{construct_absolute_images_path(relativeImagesPath)};
    if (!std::filesystem::exists(imagesPath)) {
      return imagesResult;
    }
    std::filesystem::recursive_directory_iterator rdi{imagesPath};
    for (auto it : rdi) {
      auto filePath{replace(it.path().string(), '\\', '/')};
      if (get_file_extension(filePath) == "png") {
        auto fileName{get_file_name_no_extension(filePath)};
        auto hash{forr::hash(fileName)};
        auto image{load_single_image(filePath)};
        imagesResult.insert({hash, image});
      }
    }
    return imagesResult;
  }
}