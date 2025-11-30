//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace AAK
{
    namespace Forradia
    {
        class TileDrawGroup
        {
          public:
            GLuint vao; ///< Vertex array object.

            GLuint ibo; ///< Index buffer object.

            GLuint vbo; ///< Vertex buffer object.

            int combinedIndicesCount; ///< The combined indices count.
        };
    }
}