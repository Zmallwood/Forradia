/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class image_renderer {
   public:
    void draw_image(str_view img_name, float x, float y, float w,
                    float h) const;

    void draw_image(int img_name_hash, float x, float y, float w,
                    float h) const;

    void draw_image_with_auto_height(str_view img_name, float x, float y,
                                     float w) const;
  };
}