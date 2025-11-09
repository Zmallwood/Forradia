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
    void Image2DRenderer::DrawImageByName(int uniqueRenderID, StringView imageName, float x,
                                          float y, float width, float height, bool updateExisting)
    {
        // Draw the image using the hash of the image name.

        this->DrawImageByHash(uniqueRenderID, Hash(imageName), x, y, width, height, updateExisting);
    }

    void Image2DRenderer::DrawImageByHash(int uniqueRenderID, int imageNameHash, float x, float y,
                                          float width, float height, bool updateExisting)
    {
        // Get the texture ID from the texture bank.

        auto textureID{_<TextureBank>().GetTexture(imageNameHash)};

        // Draw the image using the texture ID.

        this->DrawImageByTextureID(uniqueRenderID, textureID, x, y, width, height, updateExisting);
    }

    void Image2DRenderer::DrawImageAutoHeight(int uniqueRenderID, StringView imageName, float x,
                                              float y, float width)
    {
        // Get the hash of the image name.

        auto hash{Forradia::Hash(imageName)};

        // Get the dimensions of the image.

        auto imageDimensions{_<TextureBank>().GetTextureDimensions(hash)};

        // If the image dimensions are invalid, dont continue.

        if (imageDimensions.width <= 0 || imageDimensions.height <= 0)
        {
            return;
        }

        // Get the canvas aspect ratio.

        auto canvasAspectRatio{CalcAspectRatio(_<SDLDevice>().GetWindow())};

        // Get the aspect ratio of the image.

        auto imageAspectRatio{CFloat(imageDimensions.width) / imageDimensions.height};

        // Calculate the height of the image.

        auto height{width / imageAspectRatio * canvasAspectRatio};

        // Draw the image using the hash of the image name.

        this->DrawImageByHash(uniqueRenderID, hash, x, y, width, height);
    }
}