/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "draw_image_with_auto_height.hpp"
#include "core/image_assets/image_bank.hpp"
#include "draw_image.hpp"

namespace forr {
  void draw_image_with_auto_height(str_view image_name, float x, float y,
                                   float width) {
    auto image_name_hash{hash(image_name)};
    auto image_size{
        get_singleton<image_bank>().get_image_size(image_name_hash)};
    auto canvas_aspect_ratio{calculate_aspect_ratio()};
    auto image_aspect_ratio{c_float(image_size.w) / image_size.h};
    auto height{width / image_aspect_ratio * canvas_aspect_ratio};
    draw_image(hash(image_name), x, y, width, height);
  }
}