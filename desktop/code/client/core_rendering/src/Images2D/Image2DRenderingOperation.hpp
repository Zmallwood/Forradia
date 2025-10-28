//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class Image2DRenderingOperation
    {
      public:
        float x;

        float y;

        float width;

        float height;

        GLuint vao;

        GLuint ibo;

        GLuint vbo;
    };
}