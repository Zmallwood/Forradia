/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "image_renderer.hpp"
#include "sub/draw_image.hpp"
#include "sub/draw_image_with_auto_height.hpp"

namespace forr {
  void image_renderer::draw_image(str_view imageName, float x, float y,
                                  float width, float height) const {
    draw_image(Hash(imageName), x, y, width, height);
  }

  void image_renderer::draw_image(int imageNameHash, float x, float y,
                                  float width, float height) const {
    forr::draw_image(imageNameHash, x, y, width, height);
  }

  void image_renderer::draw_image_with_auto_height(str_view imageName, float x,
                                                   float y, float width) const {
    forr::draw_image_with_auto_height(imageName, x, y, width);
  }
}