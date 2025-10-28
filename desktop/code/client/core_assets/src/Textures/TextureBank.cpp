//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

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

        for (auto entryLevel1 : m_textTextureIDs)
        {
            for (auto entryLevel2 : entryLevel1.second)
            {
                for (auto entryLevel3 : entryLevel2.second)
                {
                    glDeleteTextures(1,
                                     &entryLevel3.second);
                }
            }
        }
    }

    GLuint TextureBank::GetTexture(int imageNameHash) const
    {
        // Check if the texture exists.

        if (m_textureEntries.contains(imageNameHash))
        {
            // If it does, return it.

            return m_textureEntries.at(imageNameHash)
                .textureID;
        }

        // If it doesn't, return error value.

        return -1;
    }

    Size TextureBank::GetTextureDimensions(
        int imageNameHash) const
    {
        // Check if the texture exists.

        if (m_textureEntries.contains(imageNameHash))
        {
            // If it does, return it.

            return m_textureEntries.at(imageNameHash)
                .dimensions;
        }

        // If it doesn't, return error value.

        return {-1, -1};
    }

    bool TextureBank::TextTextureExists(float x, float y,
                                        int textHash) const
    {
        // Return whether the text texture exists in the
        // nested map.

        return m_textTextureIDs.contains(x) &&
               m_textTextureIDs.at(x).contains(y) &&
               m_textTextureIDs.at(x).at(y).contains(
                   textHash);
    }
}