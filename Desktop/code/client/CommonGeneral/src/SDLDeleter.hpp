//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

typedef struct _TTF_Font TTF_Font;

namespace AAK
{
    namespace Forradia
    {
        ///
        /// Class used for SharedPtrs of SDL objects, which handles automaticallyfreeing up
        /// resources at object deletion.
        ///
        class SDLDeleter
        {
          public:
            ///
            /// Operator overloading for SDL_Window objects.
            ///
            /// @param window SDL window pointer to free
            /// resources for.
            ///
            void operator()(SDL_Window *window) const;

            ///
            /// Operator overloading for SDL_Renderer objects.
            ///
            /// @param renderer SDL renderer pointer to free
            /// resources for.
            ///
            void operator()(SDL_Renderer *renderer) const;

            ///
            /// Operator overloading for SDL_Surface objects.
            ///
            /// @param surface SDL surface pointer to free
            /// resources for.
            ///
            void operator()(SDL_Surface *surface) const;

            ///
            /// Operator overloading for SDL_Texture objects.
            ///
            /// @param texture SDL texture pointer to free
            /// resources for.
            ///
            void operator()(SDL_Texture *texture) const;

            ///
            /// Operator overloading for TTF_Font objects.
            ///
            /// @param font SDL font pointer to free resources
            /// for.
            ///
            void operator()(TTF_Font *font) const;
        };
    }
}