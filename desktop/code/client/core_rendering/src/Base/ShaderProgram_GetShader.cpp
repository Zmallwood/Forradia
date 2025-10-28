//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ShaderProgram.hpp"

namespace Forradia
{
    GLuint ShaderProgram::GetShader(StringView shaderSource,
                                    int shaderType) const
    {
        auto vertexShader{glCreateShader(shaderType)};

        const auto *source{
            (const GLchar *)shaderSource.data()};

        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled{0};

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS,
                      &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength{0};

            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH,
                          &maxLength);

            Vector<GLchar> infoLog(maxLength);

            glGetShaderInfoLog(vertexShader, maxLength,
                               &maxLength, &infoLog[0]);

            return 0;
        }

        return vertexShader;
    }
}