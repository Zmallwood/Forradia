/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "CanvasUtilities.hpp"
#include "Hash.hpp"
#include "Image2DRenderer.hpp"
#include "SDLDevice.hpp"
#include "Textures/TextureBank.hpp"

namespace Forradia
{
    auto Image2DRenderer::DrawImageByName(int uniqueRenderID, std::string_view imageName,
                                          float xPos, float yPos, float width, float height,
                                          bool updateExisting) -> void
    {
        this->DrawImageByHash(uniqueRenderID, Hash(imageName), xPos, yPos, width, height,
                              updateExisting);
    }

    auto Image2DRenderer::DrawImageByHash(int uniqueRenderID, int imageNameHash, float xPos,
                                          float yPos, float width, float height,
                                          bool updateExisting) -> void
    {
        auto textureID{TextureBank::GetTexture(imageNameHash)};
        this->DrawImageByTextureID(uniqueRenderID, textureID, xPos, yPos, width, height,
                                   updateExisting);
    }

    auto Image2DRenderer::DrawImageAutoHeight(int uniqueRenderID, std::string_view imageName,
                                              float xPos, float yPos, float width) -> void
    {
        auto hash{Forradia::Hash(imageName)};

        auto imageDimensions{TextureBank::GetTextureDimensions(hash)};
        if (imageDimensions.width <= 0 || imageDimensions.height <= 0)
        {
            return;
        }

        auto canvasAspectRatio{CalcAspectRatio(SDLDevice::Instance().GetWindow())};
        auto imageAspectRatio{static_cast<float>(imageDimensions.width) / imageDimensions.height};

        // Calculate the height of the image using the width and the two aspect ratios.
        auto height{width / imageAspectRatio * canvasAspectRatio};

        this->DrawImageByHash(uniqueRenderID, hash, xPos, yPos, width, height);
    }
}
