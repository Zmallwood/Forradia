//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TextureBank.hpp"

namespace Forradia
{
    GLuint TextureBank::ObtainTextTexture(float x, float y,
                                          int textHash)
    {
        // Check if the text texture exists.

        if (this->TextTextureExists(x, y, textHash))
        {
            // If it does, return it.

            return m_textTextureIDs.at(x).at(y).at(
                textHash);
        }

        // If it doesn't, create it.

        GLuint textureID;

        glGenTextures(1, &textureID);

        // Store the new texture ID in the map.

        m_textTextureIDs[x][y][textHash] = textureID;

        // Return the texture ID.

        return textureID;
    }
}