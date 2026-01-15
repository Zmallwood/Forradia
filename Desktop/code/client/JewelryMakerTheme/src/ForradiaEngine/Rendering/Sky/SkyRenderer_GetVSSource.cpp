/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "SkyRenderer.hpp"

namespace ForradiaEngine
{
    auto SkyRenderer::getVSSource() const -> std::string
    {
        return R"(
            #version 330 core
            
            layout (location = 0) in vec3 aPos;

            uniform mat4 MVP;

            out vec3 viewDirection;

            void main()
            {
                // Transform vertex to clip space.

                vec4 clipPos = MVP * vec4(aPos, 1.0);
                
                // Apply y-flip to match coordinate system.

                clipPos.y = -clipPos.y;
                
                // Force sky to render at far plane (z = w in clip space = 1.0 in NDC).

                clipPos.z = clipPos.w;
                
                gl_Position = clipPos;
                
                // Pass the view direction (normalized vertex position in model space).
                // This is the direction from center to the vertex on the unit sphere.
                
                viewDirection = normalize(aPos);
            }
        )";
    }
}
