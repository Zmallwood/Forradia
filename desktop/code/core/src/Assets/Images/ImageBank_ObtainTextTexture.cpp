//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ImageBank.hpp"

namespace Forradia
{
    GLuint ImageBank::ObtainTextTexture(float x, float y,
                                        int textHash)
    {
        if (this->TextTextureExists(x, y, textHash))
        {
            return m_textTextures.at(x).at(y).at(textHash);
        }

        GLuint texture;

        glGenTextures(1, &texture);

        m_textTextures[x][y][textHash] = texture;

        return texture;
    }
}