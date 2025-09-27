/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "DrawImageWithAutoHeight.hpp"
#include "Core/ImageAssets/ImageBank.hpp"
#include "DrawImage.hpp"

namespace Forradia
{
    void DrawImageWithAutoHeight(StringView imageName,
                                 float x,
                                 float y,
                                 float width)
    {
        auto imageNameHash{Hash(imageName)};

        auto imageSize{
            _<ImageBank>().GetImageSize(imageNameHash)};

        auto aspectRatio{
            static_cast<float>(imageSize.width) / imageSize.height};

        auto height{width / aspectRatio};

        DrawImage(Hash(imageName), x, y, width, height);
    }
}