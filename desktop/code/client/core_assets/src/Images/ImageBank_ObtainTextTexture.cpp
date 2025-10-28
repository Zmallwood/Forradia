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
            return m_textTextureIDs.at(x).at(y).at(
                textHash);
        }

        GLuint textureID;

        glGenTextures(1, &textureID);

        m_textTextureIDs[x][y][textHash] = textureID;

        return textureID;
    }
}