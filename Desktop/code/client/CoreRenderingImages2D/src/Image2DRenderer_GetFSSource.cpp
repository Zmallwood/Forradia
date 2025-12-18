/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Image2DRenderer.hpp"
#include "StdAfx.hpp"

namespace Forradia {
  auto Image2DRenderer::GetFSSource() const -> String {
    return R"(
        #version 330 core
        
        out vec4 FragColor;
            
        in vec3 ourColor;
        in vec2 TexCoord;

        uniform sampler2D ourTexture;

        void main()
        {
            FragColor = texture(ourTexture, TexCoord);
        }
    )";
  }
}
