/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Utilities/ErrorUtilities.hpp"
    #include <string_view>
// clang-format on

/* Forward declarations */ // clang-format off
    struct SDL_Window;
    struct SDL_Renderer;
    struct SDL_Texture;
    struct SDL_Surface;

    using TTF_Font = struct _TTF_Font;
// clang-format on

namespace ForradiaEngine
{
    /* Constants */ // clang-format off
        /**
        * Number of milliseconds in one second.
        */
        static constexpr int k_oneSecMillis{1000};
        /**
        * Maximum value for a color component.
        */
        static constexpr int k_maxColorComponentValue{255};
    // clang-format on

    /* Functions */ // clang-format off
        /**
        * Compute hash code from a given input text, which gets computed the same every game
        * start.
        * @param text Text to compute hash code for.
        * @return Computed hash code.
        */
        constexpr auto hash(std::string_view text) -> int
        {
            // Use djb2 algorithm by Daniel J. Bernstein.
            constexpr unsigned long algorithmConstant{5381};

            unsigned long hash{algorithmConstant};

            for (char chr : text)
            {
                constexpr unsigned long algorithmFactor{33};

                hash = algorithmFactor * hash + static_cast<unsigned char>(chr);
            }

            return static_cast<int>(hash);
        }
    // clang-format on

    /* Classes */ // clang-format off
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
    // clang-format on
}
