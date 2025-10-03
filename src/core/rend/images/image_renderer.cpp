/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "image_renderer.hpp"
#include "sub/draw_image.hpp"
#include "sub/draw_image_with_auto_height.hpp"

namespace forr {
  void image_renderer::draw_image(str_view img_name, float x, float y, float w,
                                  float h) const {
    draw_image(hash(img_name), x, y, w, h);
  }

  void image_renderer::draw_image(int img_name_hash, float x, float y, float w,
                                  float h) const {
    forr::draw_image(img_name_hash, x, y, w, h);
  }

  void image_renderer::draw_image_with_auto_height(str_view img_name, float x,
                                                   float y, float w) const {
    forr::draw_image_with_auto_height(img_name, x, y, w);
  }
}