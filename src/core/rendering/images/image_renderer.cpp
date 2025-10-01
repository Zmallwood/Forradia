/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "image_renderer.hpp"
#include "sub/draw_image.hpp"
#include "sub/draw_image_with_auto_height.hpp"

namespace forr {
  void image_renderer::DrawImage(str_view imageName, float x, float y,
                                float width, float height) const {
    DrawImage(Hash(imageName), x, y, width, height);
  }

  void image_renderer::DrawImage(int imageNameHash, float x, float y,
                                float width, float height) const {
    forr::DrawImage(imageNameHash, x, y, width, height);
  }

  void image_renderer::DrawImageWithAutoHeight(str_view imageName, float x,
                                              float y, float width) const {
    forr::DrawImageWithAutoHeight(imageName, x, y, width);
  }
}