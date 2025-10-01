/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class ImageBank {
  public:
    ImageBank() { Initialize(); }

    s_ptr<SDL_Texture> GetImage(int imageNameHash) const;

    Size GetImageSize(int imageNameHash) const;

  private:
    void Initialize();

    void LoadImages();

    inline static const str k_relativeImagesPath{"./Resources/Images/"};

    std::map<int, s_ptr<SDL_Texture>> m_images;
  };
}
