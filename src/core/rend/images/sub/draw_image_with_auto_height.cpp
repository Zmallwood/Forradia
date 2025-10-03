/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "draw_image_with_auto_height.hpp"
#include "core/core.hpp"
#include "draw_image.hpp"

namespace forr {
  void draw_image_with_auto_height(str_view img_name, float x, float y,
                                   float w) {
    auto img_name_hash{hash(img_name)};
    auto img_sz{get_singleton<image_bank>().get_image_size(img_name_hash)};
    auto canv_asp_rat{calculate_aspect_ratio()};
    auto img_asp_rat{c_float(img_sz.w) / img_sz.h};
    auto h{w / img_asp_rat * canv_asp_rat};
    draw_image(hash(img_name), x, y, w, h);
  }
}