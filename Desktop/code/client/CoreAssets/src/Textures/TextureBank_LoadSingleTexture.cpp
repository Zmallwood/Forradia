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
    GLuint TextureBank::LoadSingleTexture(SharedPtr<SDL_Surface> surface) const
    {
        // Generate a texture ID.
        GLuint textureID;

        glGenTextures(1, &textureID);

        // Bind the texture.
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Create the GL texture out from the SDL surface.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, surface->pixels);

        // Set texture parameters.

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Return the texture ID.
        return textureID;
    }
}