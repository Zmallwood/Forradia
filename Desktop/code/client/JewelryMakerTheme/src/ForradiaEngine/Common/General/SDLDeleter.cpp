/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "SDLDeleter.hpp"
    #include "ForradiaEngine/Common/Utilities/ErrorUtilities.hpp"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
// clang-format on

namespace Forradia
{
    auto SDLDeleter::operator()(SDL_Window *window) const -> void
    {
        // clang-format off - Validation
        throwOnFalse(window != nullptr, "window is null");
        // clang-format on

        SDL_DestroyWindow(window);
    }

    auto SDLDeleter::operator()(SDL_Renderer *renderer) const -> void
    {
        { // Validation
            throwOnFalse(renderer != nullptr, "renderer is null");
        }

        SDL_DestroyRenderer(renderer);
    }

    auto SDLDeleter::operator()(SDL_Surface *surface) const -> void
    {
        { // Validation
            throwOnFalse(surface != nullptr, "surface is null");
        }

        SDL_FreeSurface(surface);
    }

    auto SDLDeleter::operator()(SDL_Texture *texture) const -> void
    {
        { // Validation
            throwOnFalse(texture != nullptr, "texture is null");
        }

        SDL_DestroyTexture(texture);
    }

    auto SDLDeleter::operator()(TTF_Font *font) const -> void
    {
        { // Validation
            throwOnFalse(font != nullptr, "font is null");
        }

        TTF_CloseFont(font);
    }
}
