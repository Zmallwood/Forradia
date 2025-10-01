/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "draw_image_with_auto_height.hpp"
#include "core/image_assets/image_bank.hpp"
#include "draw_image.hpp"

namespace forr {
  void DrawImageWithAutoHeight(str_view imageName, float x, float y,
                               float width) {
    auto imageNameHash{Hash(imageName)};
    auto imageSize{GetSingleton<image_bank>().GetImageSize(imageNameHash)};
    auto canvasAspectRatio{CalculateAspectRatio()};
    auto imageAspectRatio{CFloat(imageSize.width) / imageSize.height};
    auto height{width / imageAspectRatio * canvasAspectRatio};
    DrawImage(Hash(imageName), x, y, width, height);
  }
}