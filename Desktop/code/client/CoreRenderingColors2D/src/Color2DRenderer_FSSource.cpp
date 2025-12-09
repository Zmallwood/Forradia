//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "Color2DRenderer.hpp"

namespace Forradia
{
    String Color2DRenderer::GetFSSource() const
    {
        // Return the fragment shader source.

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