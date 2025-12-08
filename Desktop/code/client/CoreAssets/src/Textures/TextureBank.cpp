//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "TextureBank.hpp"

namespace Forradia
{
    void TextureBank::Initialize()
    {
        // Load textures.
        this->LoadTextures();
    }

    void TextureBank::Cleanup()
    {
        // Delete regular textures.
        for (auto entry : m_textureEntries)
        {
            glDeleteTextures(1, &entry.second.textureID);
        }

        // Delete text textures.
        for (auto entry : m_textTextureIDs)
        {
            glDeleteTextures(1, &entry.second);
        }

        // Clear the maps.

        m_textureEntries.clear();
        m_textTextureIDs.clear();
    }

    GLuint TextureBank::GetTexture(int imageNameHash) const
    {
        // Check if the texture exists.
        if (m_textureEntries.contains(imageNameHash))
        {
            // If it does, return it.
            return m_textureEntries.at(imageNameHash).textureID;
        }

        // If it doesn't, return error value.
        return -1;
    }

    Size TextureBank::GetTextureDimensions(int imageNameHash) const
    {
        // Check if the texture exists.
        if (m_textureEntries.contains(imageNameHash))
        {
            // If it does, return it.
            return m_textureEntries.at(imageNameHash).dimensions;
        }

        // If it doesn't, return error value.
        return {-1, -1};
    }
}