/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on

namespace Forradia
{
    /**
     *  A draw group for a tile.
     */
    class TileDrawGroup
    {
      public:
        GLuint vao{};                ///< The vertex array object.
        GLuint ibo{};                ///< The index buffer object.
        GLuint vbo{};                ///< The vertex buffer object.
        int combinedIndicesCount{0}; ///< The combined indices count.
    };
}
