/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "image_bank.hpp"
#include "sub/get_image_size.hpp"
#include "sub/get_loaded_images/get_loaded_images.hpp"

namespace forr {
  void image_bank::Initialize() { LoadImages(); }

  void image_bank::LoadImages() {
    m_images = GetLoadedImages(k_relativeImagesPath);
  }

  s_ptr<SDL_Texture> image_bank::GetImage(int imageNameHash) const {
    if (m_images.contains(imageNameHash)) {
      return m_images.at(imageNameHash);
    }
    return nullptr;
  }

  size image_bank::GetImageSize(int imageNameHash) const {
    if (m_images.contains(imageNameHash)) {
      auto texture{m_images.at(imageNameHash)};
      return forr::GetImageSize(texture);
    }
    return {0, 0};
  }
}
