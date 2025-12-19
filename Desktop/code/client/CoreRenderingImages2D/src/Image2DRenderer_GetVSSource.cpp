/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Image2DRenderer.hpp"

namespace Forradia {
  auto Image2DRenderer::GetVSSource() const -> std::string {
    return R"(
        #version 330 core
        
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        layout (location = 2) in vec2 aTexCoord;

        out vec3 ourColor;
        out vec2 TexCoord;

        void main()
        {
            gl_Position = vec4(aPos, 1.0);
            gl_Position.x = gl_Position.x * 2.0 - 1.0;
            gl_Position.y = gl_Position.y * -2.0 + 1.0;
            ourColor = aColor;
            TexCoord = aTexCoord;
        }
    )";
  }
}
