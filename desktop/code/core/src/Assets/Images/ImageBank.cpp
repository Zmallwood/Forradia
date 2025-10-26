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
        this->LoadImages();
    }

    void ImageBank::Cleanup()
    {
        for (auto entry : m_textures)
        {
            glDeleteTextures(1, &entry.second);
        }

        for (auto entry1 : m_textTextures)
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
        return m_textures.at(imageNameHash);
    }

    Size ImageBank::GetImageSize(int imageNameHash) const
    {
        if (m_textureSizes.contains(imageNameHash))
        {
            return m_textureSizes.at(imageNameHash);
        }

        return {-1, -1};
    }

    bool ImageBank::TextTextureExists(float x, float y,
                                      int textHash) const
    {
        return m_textTextures.contains(x) &&
               m_textTextures.at(x).contains(y) &&
               m_textTextures.at(x).at(y).contains(
                   textHash);
    }
}