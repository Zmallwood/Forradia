/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Matter/Geometry/Size.hpp"
    #include <GL/glew.h>
    #include <GL/gl.h>
// clang-format on

namespace ForradiaEngine
{
    /**
     *  Holds information about a texture, used by the TextureBank.
     */
    class TextureEntry
    {
      public:
        GLuint textureID{}; ///< The texture ID, used by opengl.
        Size dimensions{};  ///< The texture width and height.
    };
}
