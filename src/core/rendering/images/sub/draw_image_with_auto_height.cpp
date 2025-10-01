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
    auto imageNameHash{Hash(imageName)};
    auto imageSize{GetSingleton<image_bank>().get_image_size(imageNameHash)};
    auto canvasAspectRatio{CalculateAspectRatio()};
    auto imageAspectRatio{CFloat(imageSize.width) / imageSize.height};
    auto height{width / imageAspectRatio * canvasAspectRatio};
    draw_image(Hash(imageName), x, y, width, height);
  }
}