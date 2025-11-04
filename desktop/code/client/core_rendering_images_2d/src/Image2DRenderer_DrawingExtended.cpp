//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Image2DRenderer.hpp"

#include "SDLDevice.hpp"

#include "Textures/TextureBank.hpp"

namespace Forradia
{
    void Image2DRenderer::DrawImageByName(
        StringView imageName, float x, float y, float width,
        float height)
    {
        this->DrawImageByHash(Hash(imageName), x, y, width,
                              height);
    }

    void Image2DRenderer::DrawImageByHash(
        int imageNameHash, float x, float y, float width,
        float height, bool useOperationsCache)
    {
        auto textureID{
            _<TextureBank>().GetTexture(imageNameHash)};

        this->DrawImageByTextureID(textureID, x, y, width,
                                   height,
                                   useOperationsCache);
    }

    void Image2DRenderer::DrawImageAutoHeight(
        StringView imageName, float x, float y, float width)
    {
        auto hash{Forradia::Hash(imageName)};

        auto imageDimensions{
            _<TextureBank>().GetTextureDimensions(hash)};

        if (imageDimensions.width <= 0 ||
            imageDimensions.height <= 0)
        {
            return;
        }

        auto canvasAspectRatio{
            CalcAspectRatio(_<SDLDevice>().GetWindow())};

        auto imageAspectRatio{
            CFloat(imageDimensions.width) /
            imageDimensions.height};

        auto height{width / imageAspectRatio *
                    canvasAspectRatio};

        this->DrawImageByHash(hash, x, y, width, height);
    }
}