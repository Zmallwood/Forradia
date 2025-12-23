/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Geometry/Size.hpp"
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on

namespace Forradia
{
    /**
        Holds information about a texture, used by the TextureBank.
     */
    class TextureEntry
    {
      public:
        GLuint textureID{}; ///< The texture ID, used by opengl.
        Size dimensions{};  ///< The texture width and height.
    };
}
