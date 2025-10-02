/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "image_renderer.hpp"
#include "sub/draw_image.hpp"
#include "sub/draw_image_with_auto_height.hpp"

namespace forr {
  void image_renderer::draw_image(str_view image_name, float x, float y,
                                  float width, float height) const {
    draw_image(hash(image_name), x, y, width, height);
  }

  void image_renderer::draw_image(int image_name_hash, float x, float y,
                                  float width, float height) const {
    forr::draw_image(image_name_hash, x, y, width, height);
  }

  void image_renderer::draw_image_with_auto_height(str_view image_name, float x,
                                                   float y, float width) const {
    forr::draw_image_with_auto_height(image_name, x, y, width);
  }
}