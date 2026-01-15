/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

namespace ForradiaEngine
{
    /**
     *  A rendering operation for colors in 2D.
     */
    class Color2DRenderingOperation
    {
      public:
        GLuint vao{}; ///< The vertex array object.
        GLuint ibo{}; ///< The index buffer object.
        GLuint vbo{}; ///< The vertex buffer object.
    };
}
