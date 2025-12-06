//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "TileData.hpp"

namespace Forradia
{
    ///
    /// A rendering operation for a ground tile.
    ///
    class GroundRenderingOperation
    {
      public:
        GLuint vao; ///< Vertex array object.

        GLuint ibo; ///< Index buffer object.

        GLuint vbo; ///< Vertex buffer object.
    };
}