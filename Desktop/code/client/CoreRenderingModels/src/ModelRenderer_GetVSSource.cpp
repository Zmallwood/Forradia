/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ModelRenderer.hpp"

namespace Forradia {
    auto ModelRenderer::GetVSSource() const -> std::string {
        return R"(
            #version 330 core
            
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aNormal;
            layout (location = 2) in vec2 aTexCoord;

            out vec3 FragPos;
            out vec3 Normal;
            out vec2 TexCoord;

            uniform mat4 projection; 
            uniform mat4 view; 
            uniform mat4 model;

            uniform float scale;

            void main()
            {
                FragPos = vec3(model * vec4(aPos, 1.0));
                Normal = vec3(model * vec4(aNormal, 0.0));
                gl_Position = projection * view * vec4(FragPos, 1.0);
                gl_Position.y = gl_Position.y * -1.0;
                TexCoord = aTexCoord;
            }
        )";
    }
}
