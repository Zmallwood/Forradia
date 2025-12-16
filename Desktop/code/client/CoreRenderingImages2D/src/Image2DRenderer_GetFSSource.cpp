//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "Image2DRenderer.hpp"

namespace Forradia {
    String Image2DRenderer::GetFSSource() const {
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