/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Image2DRenderer.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Common/General.hpp"
#include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
#include "ForradiaEngine/Assets/Textures/TextureBank.hpp"

namespace ForradiaEngine
{
    auto Image2DRenderer::drawImageByName(int uniqueRenderID, std::string_view imageName,
                                          float xPos, float yPos, float width, float height,
                                          bool updateExisting) -> void
    {
        this->drawImageByHash(uniqueRenderID, hash(imageName), xPos, yPos, width, height,
                              updateExisting);
    }

    auto Image2DRenderer::drawImageByHash(int uniqueRenderID, int imageNameHash, float xPos,
                                          float yPos, float width, float height,
                                          bool updateExisting) -> void
    {
        auto textureID{TextureBank::instance().getTexture(imageNameHash)};
        this->drawImageByTextureID(uniqueRenderID, textureID, xPos, yPos, width, height,
                                   updateExisting);
    }

    auto Image2DRenderer::drawImageAutoHeight(int uniqueRenderID, std::string_view imageName,
                                              float xPos, float yPos, float width) -> void
    {
        auto hash{ForradiaEngine::hash(imageName)};

        auto imageDimensions{TextureBank::getTextureDimensions(hash)};
        if (imageDimensions.width <= 0 || imageDimensions.height <= 0)
        {
            return;
        }

        auto canvasAspectRatio{calcAspectRatio(SDLDevice::instance().getWindow())};
        auto imageAspectRatio{static_cast<float>(imageDimensions.width) / imageDimensions.height};

        // Calculate the height of the image using the width and the two aspect ratios.
        auto height{width / imageAspectRatio * canvasAspectRatio};

        this->drawImageByHash(uniqueRenderID, hash, xPos, yPos, width, height);
    }
}
