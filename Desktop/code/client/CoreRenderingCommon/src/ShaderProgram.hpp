/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia {
    /**
     * Shader program which is used for each renderer.
     */
    class ShaderProgram {
      public:
        /**
         * Initialize the shader program.
         *
         * @param vertexShaderSource Vertex shader source.
         * @param fragmentShaderSource Fragment shader source.
         */
        ShaderProgram(std::string_view vertexShaderSource, std::string_view fragmentShaderSource) {
            this->Initialize(vertexShaderSource, fragmentShaderSource);
        }

        /**
         * Cleanup the shader program.
         */
        ~ShaderProgram() {
            this->Cleanup();
        }

        /**
         * Get the program ID.
         *
         * @return The program ID.
         */
        auto GetProgramID() const {
            return m_programID;
        }

      private:
        auto Initialize(std::string_view vertexShaderSource, std::string_view fragmentShaderSource)
            -> void;

        auto Cleanup() -> void;

        auto GetShader(std::string_view shaderSource, int shaderType) const -> GLuint;

        auto CreateProgram(GLuint vertexShader, GLuint fragmentShader) -> GLint;

        GLuint m_programID;
    };
}
