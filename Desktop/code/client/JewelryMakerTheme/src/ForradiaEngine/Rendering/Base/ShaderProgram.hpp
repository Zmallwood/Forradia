/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <string_view>
#include <GL/glew.h>
#include <GL/gl.h>

namespace ForradiaEngine
{
    /**
     *  Shader program which is used for each renderer.
     */
    class ShaderProgram
    {
      public:
        /**
         *  Initialize the shader program.
         *
         *  @param vertexShaderSource Vertex shader source.
         *  @param fragmentShaderSource Fragment shader source.
         */
        ShaderProgram(std::string_view vertexShaderSource, std::string_view fragmentShaderSource)
        {
            this->initialize(vertexShaderSource, fragmentShaderSource);
        }

        /**
         *  Cleanup the shader program.
         */
        ~ShaderProgram()
        {
            this->cleanup();
        }

        /**
         *  Get the program ID.
         *
         *  @return The program ID.
         */
        [[nodiscard]] auto getProgramID() const
        {
            return m_programID;
        }

      private:
        auto initialize(std::string_view vertexShaderSource, std::string_view fragmentShaderSource)
            -> void;

        auto cleanup() -> void;

        [[nodiscard]] static auto getShader(std::string_view shaderSource, int shaderType)
            -> GLuint;

        auto createProgram(GLuint vertexShader, GLuint fragmentShader) -> GLint;

        GLuint m_programID{};
    };
}
