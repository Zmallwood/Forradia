/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "draw_image_with_auto_height.hpp"
#include "core/image_assets/image_bank.hpp"
#include "draw_image.hpp"

namespace forr {
  void draw_image_with_auto_height(str_view imageName, float x, float y,
                                   float width) {
    auto imageNameHash{hash(imageName)};
    auto imageSize{get_singleton<image_bank>().get_image_size(imageNameHash)};
    auto canvasAspectRatio{calculate_aspect_ratio()};
    auto imageAspectRatio{c_float(imageSize.w) / imageSize.h};
    auto height{width / imageAspectRatio * canvasAspectRatio};
    draw_image(hash(imageName), x, y, width, height);
  }
}