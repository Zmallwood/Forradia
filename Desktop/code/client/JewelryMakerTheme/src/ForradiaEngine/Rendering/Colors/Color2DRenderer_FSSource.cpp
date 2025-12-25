/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Color2DRenderer.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto Color2DRenderer::getFSSource() const -> std::string
    {
        return R"(
          #version 330 core
          
          out vec4 FragColor;
              
          in vec4 ourColor;

          void main()
          {
              FragColor = ourColor;
          }
        )";
    }
}
