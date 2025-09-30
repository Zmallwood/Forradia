/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "DrawImageWithAutoHeight.hpp"
#include "core/image_assets/ImageBank.hpp"
#include "DrawImage.hpp"

namespace Forradia {
  void DrawImageWithAutoHeight(StringView imageName, float x, float y,
                               float width) {
    auto imageNameHash{Hash(imageName)};

    auto imageSize{GetSingleton<ImageBank>().GetImageSize(imageNameHash)};

    auto canvasAspectRatio{CalculateAspectRatio()};

    auto imageAspectRatio{CFloat(imageSize.width) / imageSize.height};

    auto height{width / imageAspectRatio * canvasAspectRatio};

    DrawImage(Hash(imageName), x, y, width, height);
  }
}