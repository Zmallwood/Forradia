/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "ImageBank.hpp"
#include "sub/GetImageSize.hpp"
#include "sub/get_loaded_images/GetLoadedImages.hpp"

namespace Forradia {
  void ImageBank::Initialize() { LoadImages(); }

  void ImageBank::LoadImages() {
    m_images = GetLoadedImages(k_relativeImagesPath);
  }

  SharedPtr<SDL_Texture> ImageBank::GetImage(int imageNameHash) const {
    if (m_images.contains(imageNameHash)) {
      return m_images.at(imageNameHash);
    }

    return nullptr;
  }

  Size ImageBank::GetImageSize(int imageNameHash) const {
    if (m_images.contains(imageNameHash)) {
      auto texture{m_images.at(imageNameHash)};

      return Forradia::GetImageSize(texture);
    }

    return {0, 0};
  }
}
