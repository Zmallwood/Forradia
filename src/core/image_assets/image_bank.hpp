/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class image_bank {
  public:
    image_bank() { initialize(); }

    s_ptr<SDL_Texture> get_image(int imageNameHash) const;

    size get_image_size(int imageNameHash) const;

  private:
    void initialize();

    void load_images();

    inline static const str k_relativeImagesPath{"./Resources/Images/"};

    std::map<int, s_ptr<SDL_Texture>> m_images;
  };
}
