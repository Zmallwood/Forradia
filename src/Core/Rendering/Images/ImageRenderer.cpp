/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "ImageRenderer.hpp"
#include "Sub/DrawImage.hpp"
#include "Sub/DrawImageWithAutoHeight.hpp"

namespace Forradia
{
    void ImageRenderer::DrawImage(std::string_view imageName,
                                  float x,
                                  float y,
                                  float width,
                                  float height) const
    {
        DrawImage(Hash(imageName), x, y, width, height);
    }

    void ImageRenderer::DrawImage(int imageNameHash,
                                  float x,
                                  float y,
                                  float width,
                                  float height) const
    {
        Forradia::DrawImage(imageNameHash, x, y, width, height);
    }

    void ImageRenderer::DrawImageWithAutoHeight(std::string_view imageName,
                                  float x,
                                  float y,
                                  float width) const
    {
        Forradia::DrawImageWithAutoHeight(imageName, x, y, width);
    }
}