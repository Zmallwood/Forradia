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
        String GroundRenderer::GetFSSource() const
        {
            // Return the fragment shader source.

            return R"(
                #version 330 core
                
                out vec4 FragColor;
                    
                in vec3 ourColor;
                in vec2 TexCoord;
                in vec3 Normal;

                uniform sampler2D ourTexture;

                void main()
                {
                    vec3 lightColor = vec3(1.0, 1.0, 0.8);
                    vec3 norm = normalize(Normal);
                    vec3 lightDir = vec3(10.0, 10.0, 20.0);
                    float diff = max(dot(norm, lightDir), 0.0);
                    vec3 diffuse = diff * lightColor*0.05;
                    vec4 objectColor = texture(ourTexture, TexCoord);
                    vec3 result = diffuse* objectColor.rgb;
                    FragColor = vec4(result, objectColor.a);
                }
            )";
        }
    }
}