/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GroundRenderer.hpp"

namespace Forradia
{
    auto GroundRenderer::getFSSource() const -> std::string
    {
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

                //vec4 objectColor = texture(ourTexture, TexCoord);
                //vec3 baseColor = ourColor * objectColor.rgb;
                //vec3 result = diffuse * baseColor;

                vec4 objectColor = texture(ourTexture, TexCoord);
                vec3 finalColor = objectColor.rgb * ourColor;  // Gray * Color = Color
                vec3 result = diffuse * finalColor;

                //vec4 objectColor = texture(ourTexture, TexCoord);
                //vec3 tintedColor = objectColor.rgb * ourColor;
                //vec3 result = diffuse * tintedColor;
                
                //vec3 blendedColor = mix(objectColor.rgb, ourColor, 0.5);
                //vec3 result = diffuse * blendedColor;
                //vec3 result = diffuse * objectColor.rgb * ourColor;
                //vec3 result = diffuse* objectColor.rgb;
                //vec3 baseColor = ourColor * objectColor.rgb;
                //vec3 result = diffuse * baseColor;
                //vec3 result = diffuse * (objectColor.rgb + ourColor * 0.2);

                FragColor = vec4(result, objectColor.a);
            }
        )";
    }
}
