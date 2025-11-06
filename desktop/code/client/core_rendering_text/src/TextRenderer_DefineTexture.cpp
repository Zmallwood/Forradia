//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "TextRenderer.hpp"

namespace Forradia
{
    void TextRenderer::DefineTexture(
        SharedPtr<SDL_Surface> surface) const
    {
        auto intermediary{SharedPtr<SDL_Surface>(
            SDL_CreateRGBSurface(0, surface->w, surface->h,
                                 32, 0x000000ff, 0x0000ff00,
                                 0x00ff0000, 0xff000000),
            SDLDeleter())};

        SDL_BlitSurface(surface.get(), 0,
                        intermediary.get(), 0);

        glTexImage2D(GL_TEXTURE_2D, 0, 4, intermediary->w,
                     intermediary->h, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     intermediary->pixels);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}