/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "ImageRenderer.hpp"
#include "Core/ImageAssets/ImageBank.hpp"
#include "Core/SDLDevice/SDLDevice.hpp"

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
        auto image{
            _<ImageBank>().GetImage(imageNameHash)};

        auto canvasSize{GetCanvasSize()};

        auto xPx{static_cast<int>(x * canvasSize.width)};

        auto yPx{static_cast<int>(y * canvasSize.height)};

        auto widthPx{static_cast<int>(width * canvasSize.width)};

        auto heightPx{static_cast<int>(height * canvasSize.height)};

        SDL_Rect sdlRectangle{xPx, yPx, widthPx, heightPx};

        SDL_RenderCopy(
            _<SDLDevice>().GetRenderer().get(),
            image.get(),
            nullptr,
            &sdlRectangle);
    }

    void ImageRenderer::DrawImage(std::string_view imageName,
                                  float x,
                                  float y,
                                  float width) const
    {
        auto imageNameHash{Hash(imageName)};

        auto imageSize{
            _<ImageBank>().GetImageSize(imageNameHash)};

        auto aspectRatio{
            static_cast<float>(imageSize.width) / imageSize.height};

        auto height{width / aspectRatio};

        DrawImage(imageName, x, y, width, height);
    }
}