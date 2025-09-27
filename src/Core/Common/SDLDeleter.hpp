/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class SDLDeleter
    {
    public:
        void operator()(SDL_Window *window) const;

        void operator()(SDL_Renderer *renderer) const;

        void operator()(SDL_Surface *surface) const;

        void operator()(SDL_Texture *texture) const;

        void operator()(TTF_Font *font) const;
    };
}
