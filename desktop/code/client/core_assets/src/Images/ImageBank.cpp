//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ImageBank.hpp"

namespace Forradia
{
    void ImageBank::Initialize()
    {
        this->LoadTextures();
    }

    void ImageBank::Cleanup()
    {
        for (auto entry : m_textureEntries)
        {
            glDeleteTextures(1, &entry.second.textureID);
        }

        for (auto entry1 : m_textTextureIDs)
        {
            for (auto entry2 : entry1.second)
            {
                for (auto texture : entry2.second)
                {
                    glDeleteTextures(1, &texture.second);
                }
            }
        }
    }

    GLuint ImageBank::GetTexture(int imageNameHash) const
    {
        return m_textureEntries.at(imageNameHash).textureID;
    }

    Size
    ImageBank::GetTextureDimensions(int imageNameHash) const
    {
        if (m_textureEntries.contains(imageNameHash))
        {
            return m_textureEntries.at(imageNameHash)
                .dimensions;
        }

        return {-1, -1};
    }

    bool ImageBank::TextTextureExists(float x, float y,
                                      int textHash) const
    {
        return m_textTextureIDs.contains(x) &&
               m_textTextureIDs.at(x).contains(y) &&
               m_textTextureIDs.at(x).at(y).contains(
                   textHash);
    }
}