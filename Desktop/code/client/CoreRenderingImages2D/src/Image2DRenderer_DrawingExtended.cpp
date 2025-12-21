/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Image2DRenderer.hpp"
#include "SDLDevice.hpp"
#include "Textures/TextureBank.hpp"

namespace Forradia {
    auto Image2DRenderer::DrawImageByName(int uniqueRenderID, std::string_view imageName, float x,
                                          float y, float width, float height, bool updateExisting)
        -> void {
        this->DrawImageByHash(uniqueRenderID, Hash(imageName), x, y, width, height, updateExisting);
    }

    auto Image2DRenderer::DrawImageByHash(int uniqueRenderID, int imageNameHash, float x, float y,
                                          float width, float height, bool updateExisting) -> void {
        auto textureID{Singleton<TextureBank>().GetTexture(imageNameHash)};
        this->DrawImageByTextureID(uniqueRenderID, textureID, x, y, width, height, updateExisting);
    }

    auto Image2DRenderer::DrawImageAutoHeight(int uniqueRenderID, std::string_view imageName,
                                              float x, float y, float width) -> void {
        auto hash{Forradia::Hash(imageName)};
        auto imageDimensions{Singleton<TextureBank>().GetTextureDimensions(hash)};
        if (imageDimensions.width <= 0 || imageDimensions.height <= 0)
            return;

        auto canvasAspectRatio{CalcAspectRatio(Singleton<SDLDevice>().GetWindow())};
        auto imageAspectRatio{static_cast<float>(imageDimensions.width) / imageDimensions.height};

        // Calculate the height of the image using the width and the two aspect ratios.
        auto height{width / imageAspectRatio * canvasAspectRatio};

        this->DrawImageByHash(uniqueRenderID, hash, x, y, width, height);
    }
}
