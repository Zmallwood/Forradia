/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "TileData.hpp"
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on

namespace Forradia
{
    /**
     * A rendering operation for a ground tile.
     */
    class GroundRenderingOperation
    {
      public:
        GLuint vao{}; ///< The vertex array object.
        GLuint ibo{}; ///< The index buffer object.
        GLuint vbo{}; ///< The vertex buffer object.
    };
}
