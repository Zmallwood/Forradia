//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia
{
    ///
    /// Shader program which is used for each renderer.
    ///
    class ShaderProgram
    {
      public:
        ///
        /// Constructor.
        ///
        /// @param vertexShaderSource Vertex shader source.
        /// @param fragmentShaderSource Fragment shader source.
        ///
        ShaderProgram(StringView vertexShaderSource, StringView fragmentShaderSource)
        {
            this->Initialize(vertexShaderSource, fragmentShaderSource);
        }

        ///
        /// Destructor.
        ///
        ~ShaderProgram()
        {
            this->Cleanup();
        }

        ///
        /// Gets the program ID.
        ///
        /// @return The program ID.
        ///
        auto GetProgramID() const
        {
            return m_programID;
        }

      private:
        ///
        /// Initialize the shader program by creating the vertex and fragment shaders and
        /// linking the program.
        ///
        /// @param vertexShaderSource Vertex shader source.
        /// @param fragmentShaderSource Fragment shader source.
        ///
        void Initialize(StringView vertexShaderSource, StringView fragmentShaderSource);

        ///
        /// Cleanup the shader program.
        ///
        void Cleanup();

        ///
        /// Gets a shader compiled from the given source.
        ///
        /// @param shaderSource The shader source.
        /// @param shaderType The shader type: GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
        /// @return The shader ID.
        ///
        GLuint GetShader(StringView shaderSource, int shaderType) const;

        ///
        /// Creates the linked shader program.
        ///
        /// @param vertexShader The vertex shader ID.
        /// @param fragmentShader The fragment shader ID.
        /// @return The program ID.
        ///
        GLint CreateProgram(GLuint vertexShader, GLuint fragmentShader);

        GLuint m_programID; ///< The shader program ID.
    };
}