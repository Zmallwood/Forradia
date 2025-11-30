//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GroundRenderer.hpp"

namespace AAK
{
    namespace Forradia
    {
        String GroundRenderer::GetVSSource() const
        {
            // Return the vertex shader source.

            return R"(
                #version 330 core
                
                layout (location = 0) in vec3 aPos;
                layout (location = 1) in vec3 aColor;
                layout (location = 2) in vec2 aTexCoord;
                layout (location = 3) in vec3 aNormal;

                uniform mat4 MVP;

                out vec3 ourColor;
                out vec2 TexCoord;
                out vec3 Normal;

                void main()
                {
                    vec4 v = vec4(aPos, 1.0);
                    gl_Position = MVP * v;
                    gl_Position.y = gl_Position.y * -1.0;
                    ourColor = aColor;
                    TexCoord = aTexCoord;
                    Normal = aNormal;
                }
            )";
        }
    }
}