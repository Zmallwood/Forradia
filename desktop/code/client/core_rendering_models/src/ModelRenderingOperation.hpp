//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// A model rendering operation.
    ///
    class ModelRenderingOperation
    {
      public:
        int verticesCount; ///< The number of vertices in the model.

        GLuint vao; ///< The vertex array object.

        GLuint ibo; ///< The index buffer object.

        GLuint vbo; ///< The vertex buffer object.
    };
}