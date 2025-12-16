//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "ShaderProgram.hpp"

namespace Forradia {
    GLuint ShaderProgram::GetShader(StringView shaderSource, int shaderType) const {
        // Create a new shader.
        auto shader{glCreateShader(shaderType)};

        // Get the shader source in correct format.
        const auto *source{(const GLchar *)shaderSource.data()};

        // Compile the shader.

        glShaderSource(shader, 1, &source, 0);

        glCompileShader(shader);

        // Get the compile status.

        GLint isCompiled{0};

        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

        // If the compile failed.
        if (isCompiled == GL_FALSE) {
            // Get the length of the info log.

            GLint maxLength{0};

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // Get the info log.

            Vector<GLchar> infoLog(maxLength);

            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            // Return failed status.
            return 0;
        }

        // Return the shader.
        return shader;
    }
}