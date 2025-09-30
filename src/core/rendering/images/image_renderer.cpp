/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "image_renderer.hpp"
#include "sub/draw_image.hpp"
#include "sub/draw_image_with_auto_height.hpp"

namespace Forradia {
  void ImageRenderer::DrawImage(StringView imageName, float x, float y,
                                float width, float height) const {
    DrawImage(Hash(imageName), x, y, width, height);
  }

  void ImageRenderer::DrawImage(int imageNameHash, float x, float y,
                                float width, float height) const {
    Forradia::DrawImage(imageNameHash, x, y, width, height);
  }

  void ImageRenderer::DrawImageWithAutoHeight(StringView imageName, float x,
                                              float y, float width) const {
    Forradia::DrawImageWithAutoHeight(imageName, x, y, width);
  }
}