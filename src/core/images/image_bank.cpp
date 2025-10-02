/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "image_bank.hpp"
#include "sub/get_image_size.hpp"
#include "sub/get_loaded_images/get_loaded_images.hpp"

namespace forr {
  void image_bank::initialize() { load_images(); }

  void image_bank::load_images() {
    m_images = get_loaded_images(k_relative_images_path);
  }

  s_ptr<SDL_Texture> image_bank::get_image(int image_name_hash) const {
    if (m_images.contains(image_name_hash)) {
      return m_images.at(image_name_hash);
    }
    return nullptr;
  }

  size image_bank::get_image_size(int image_name_hash) const {
    if (m_images.contains(image_name_hash)) {
      auto texture{m_images.at(image_name_hash)};
      return forr::get_image_size(texture);
    }
    return {0, 0};
  }
}
