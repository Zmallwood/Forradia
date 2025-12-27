/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "TextureBank.hpp"
    
    #include <ranges>
// clang-format on

namespace ForradiaEngine
{
    auto TextureBank::initialize() -> void
    {
        TextureBank::loadTextures();
    }

    auto TextureBank::cleanup() -> void
    {
        for (auto val : m_textureEntries | std::views::values)
        {
            glDeleteTextures(1, &val.textureID);
        }

        for (auto val : m_textTextureIDs | std::views::values)
        {
            glDeleteTextures(1, &val);
        }

        m_textureEntries.clear();
        
        m_textTextureIDs.clear();
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    auto TextureBank::getTexture(int imageNameHash) const -> GLuint
    {
        if (m_textureEntries.contains(imageNameHash))
        {
            return m_textureEntries.at(imageNameHash).textureID;
        }

        return -1;
    }

    auto TextureBank::getTextureDimensions(int imageNameHash) -> Size
    {
        if (m_textureEntries.contains(imageNameHash))
        {
            return m_textureEntries.at(imageNameHash).dimensions;
        }

        return {-1, -1};
    }
}
