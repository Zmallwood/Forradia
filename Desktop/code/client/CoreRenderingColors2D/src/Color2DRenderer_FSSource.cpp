/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Color2DRenderer.hpp"

namespace Forradia {
  auto Color2DRenderer::GetFSSource() const -> std::string {
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
