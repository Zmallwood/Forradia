/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Forward declarations */ // clang-format off
    struct SDL_Window;
    struct SDL_Renderer;
    struct SDL_Texture;
    struct SDL_Surface;

    using TTF_Font = struct _TTF_Font;
// clang-format on

namespace ForradiaEngine
{
    /**
     *  Class used for SharedPtrs of SDL objects, which handles automatically freeing up
     *  resources at object deletion.
     *
     *  @return The SDLDeleter object.
     */
    class SDLDeleter
    {
      public:
        /**
         *  Operator overloading for SDL_Window objects.
         *
         *  @param window SDL window pointer to free resources for.
         */
        auto operator()(SDL_Window *window) const -> void;

        /**
         *  Operator overloading for SDL_Renderer objects.
         *
         *  @param renderer SDL renderer pointer to free resources for.
         */
        auto operator()(SDL_Renderer *renderer) const -> void;

        /**
         *  Operator overloading for SDL_Surface objects.
         *
         *  @param surface SDL surface pointer to free resources for.
         */
        auto operator()(SDL_Surface *surface) const -> void;

        /**
         *  Operator overloading for SDL_Texture objects.
         *
         *  @param texture SDL texture pointer to free resources for.
         */
        auto operator()(SDL_Texture *texture) const -> void;

        /**
         *  Operator overloading for TTF_Font objects.
         *
         *  @param font SDL font pointer to free resources for.
         */
        auto operator()(TTF_Font *font) const -> void;
    };
}
