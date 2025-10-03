/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class image_renderer {
   public:
    void draw_img(str_view img_name, float x, float y, float w, float h) const;

    void draw_img(int img_name_hash, float x, float y, float w, float h) const;

    void draw_img_auto_h(str_view img_name, float x, float y, float w) const;
  };
}