/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "General.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "ForradiaEngine/Common/Utilities.hpp"

namespace ForradiaEngine
{
    auto SDLDeleter::operator()(SDL_Window *window) const -> void
    {
        throwOnFalse(window != nullptr, "window is null");

        SDL_DestroyWindow(window);
    }

    auto SDLDeleter::operator()(SDL_Renderer *renderer) const -> void
    {
        throwOnFalse(renderer != nullptr, "renderer is null");

        SDL_DestroyRenderer(renderer);
    }

    auto SDLDeleter::operator()(SDL_Surface *surface) const -> void
    {
        throwOnFalse(surface != nullptr, "surface is null");

        SDL_FreeSurface(surface);
    }

    auto SDLDeleter::operator()(SDL_Texture *texture) const -> void
    {
        throwOnFalse(texture != nullptr, "texture is null");

        SDL_DestroyTexture(texture);
    }

    auto SDLDeleter::operator()(TTF_Font *font) const -> void
    {
        throwOnFalse(font != nullptr, "font is null");

        TTF_CloseFont(font);
    }

    auto SDLDeleter::operator()(Mix_Chunk *chunk) const -> void
    {
        throwOnFalse(chunk != nullptr, "chunk is null");

        Mix_FreeChunk(chunk);
    }

    auto SDLDeleter::operator()(Mix_Music *music) const -> void
    {
        throwOnFalse(music != nullptr, "music is null");

        Mix_FreeMusic(music);
    }
}
