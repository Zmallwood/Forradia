//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TextureBank.hpp"

namespace Forradia
{
    bool TextureBank::ObtainTextTexture(int uniqueTextureID, GLuint &textureID)
    {
        // Check if the text texture exists.

        if (m_textTextureIDs.contains(uniqueTextureID))
        {
            // If it does, set the texture ID and return true, indicating that the texture
            // already exists.

            textureID = m_textTextureIDs.at(uniqueTextureID);

            return true;
        }

        // If it doesn't, create it.

        glGenTextures(1, &textureID);

        // Store the new texture ID in the map.

        m_textTextureIDs[uniqueTextureID] = textureID;

        // Return false, indicating that the texture was not found.

        return false;
    }
}