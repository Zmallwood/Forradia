/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <string>
// clang-format on

namespace ForradiaEngine
{
    /**
     *  A texture, primarily used for models.
     */
    class Texture
    {
      public:
        /**
         *  Constructor for the Texture class.
         *
         *  @param path The path to the texture.
         */
        Texture(std::string_view path) : path(path)
        {
        }

        std::string path{}; ///< The path to the texture.
    };
}
