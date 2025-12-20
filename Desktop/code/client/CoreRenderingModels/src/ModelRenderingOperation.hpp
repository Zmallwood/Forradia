/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia {
    /**
     * A model rendering operation.
     */
    class ModelRenderingOperation {
      public:
        /**
         * The number of vertices in the model.
         */
        int verticesCount;

        /**
         * The vertex array object.
         */
        GLuint vao;

        /**
         * The index buffer object.
         */
        GLuint ibo;

        /**
         * The vertex buffer object.
         */
        GLuint vbo;
    };
}
