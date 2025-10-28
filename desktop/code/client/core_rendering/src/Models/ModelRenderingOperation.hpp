//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class ModelRenderingOperation
    {
      public:
        float x;

        float y;

        float z;

        int verticesCount;

        GLuint vao;

        GLuint ibo;

        GLuint vbo;
    };
}