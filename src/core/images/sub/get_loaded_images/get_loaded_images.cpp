/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "get_loaded_images.hpp"
#include "../load_single_image.hpp"
#include "sub/construct_absolute_images_path.hpp"

namespace forr {
  std::map<int, s_ptr<SDL_Texture>>
  get_loaded_images(str_view relative_images_path) {
    std::map<int, s_ptr<SDL_Texture>> images_result;
    auto images_path{construct_absolute_images_path(relative_images_path)};
    if (!std::filesystem::exists(images_path)) {
      return images_result;
    }
    std::filesystem::recursive_directory_iterator rdi{images_path};
    for (auto it : rdi) {
      auto file_path{replace(it.path().string(), '\\', '/')};
      if (get_file_extension(file_path) == "png") {
        auto file_name{get_file_name_no_extension(file_path)};
        auto hash{forr::hash(file_name)};
        auto image{load_single_image(file_path)};
        images_result.insert({hash, image});
      }
    }
    return images_result;
  }
}