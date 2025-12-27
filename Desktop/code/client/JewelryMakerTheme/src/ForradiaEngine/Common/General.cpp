/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "General.hpp"
    
    #include "ForradiaEngine/Common/Utilities.hpp"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
// clang-format on

namespace ForradiaEngine
{
    /* Classes */ // clang-format off
        auto SDLDeleter::operator()(SDL_Window *window) const -> void
        {
            /* Validation */ // clang-format off
            throwOnFalse(window != nullptr, "window is null");
            // clang-format on */

            SDL_DestroyWindow(window);
        }

        auto SDLDeleter::operator()(SDL_Renderer *renderer) const -> void
        {
            /* Validation */ // clang-format off
                throwOnFalse(renderer != nullptr, "renderer is null");
            // clang-format on */

            SDL_DestroyRenderer(renderer);
        }

        auto SDLDeleter::operator()(SDL_Surface *surface) const -> void
        {
            /* Validation */ // clang-format off
                throwOnFalse(surface != nullptr, "surface is null");
            // clang-format on */

            SDL_FreeSurface(surface);
        }

        auto SDLDeleter::operator()(SDL_Texture *texture) const -> void
        {
            /* Validation */ // clang-format off
                throwOnFalse(texture != nullptr, "texture is null");
            // clang-format on */

            SDL_DestroyTexture(texture);
        }

        auto SDLDeleter::operator()(TTF_Font *font) const -> void
        {
            /* Validation */ // clang-format off
                throwOnFalse(font != nullptr, "font is null");
            // clang-format on */

            TTF_CloseFont(font);
        }
    // clang-format on
}
