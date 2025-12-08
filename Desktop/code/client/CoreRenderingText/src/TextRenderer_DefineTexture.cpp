//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "TextRenderer.hpp"

namespace Forradia
{
    void TextRenderer::DefineTexture(SharedPtr<SDL_Surface> surface) const
    {
        // Create an intermediary surface with RGBA format for OpenGL compatibility.

        auto intermediary{
            SharedPtr<SDL_Surface>(SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0x000000ff,
                                                        0x0000ff00, 0x00ff0000, 0xff000000),
                                   SDLDeleter())};

        // Copy the source surface data to the intermediary surface.

        SDL_BlitSurface(surface.get(), 0, intermediary.get(), 0);

        // Upload the surface pixel data to the OpenGL texture.

        glTexImage2D(GL_TEXTURE_2D, 0, 4, intermediary->w, intermediary->h, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, intermediary->pixels);

        // Set the texture minification filter to linear interpolation.

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Set the texture magnification filter to linear interpolation.

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}