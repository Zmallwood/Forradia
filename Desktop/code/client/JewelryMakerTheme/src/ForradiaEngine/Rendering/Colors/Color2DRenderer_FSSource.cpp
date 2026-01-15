/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Color2DRenderer.hpp"

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
