/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Image2DRenderer.hpp"
// clang-format on

namespace Forradia
{
    auto Image2DRenderer::getFSSource() const -> std::string
    {
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
