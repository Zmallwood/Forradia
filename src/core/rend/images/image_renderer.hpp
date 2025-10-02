/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class image_renderer {
   public:
    void draw_image(str_view image_name, float x, float y, float width,
                    float height) const;

    void draw_image(int image_name_hash, float x, float y, float width,
                    float height) const;

    void draw_image_with_auto_height(str_view image_name, float x, float y,
                                     float width) const;
  };
}