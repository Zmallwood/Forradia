//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ShaderProgram.hpp"

namespace Forradia
{
    void ShaderProgram::Initialize(
        StringView vertexShaderSource,
        StringView fragmentShaderSource)
    {
        auto vertexShader{GetShader(vertexShaderSource,
                                    GL_VERTEX_SHADER)};

        if (0 == vertexShader)
        {
            glDeleteShader(vertexShader);

            return;
        }

        auto fragmentShader{GetShader(fragmentShaderSource,
                                      GL_FRAGMENT_SHADER)};

        if (0 == fragmentShader)
        {
            glDeleteShader(vertexShader);

            glDeleteShader(fragmentShader);

            return;
        }

        m_programID = glCreateProgram();

        glAttachShader(m_programID, vertexShader);

        glAttachShader(m_programID, fragmentShader);

        glLinkProgram(m_programID);

        GLint isLinked{0};

        glGetProgramiv(m_programID, GL_LINK_STATUS,
                       (int *)&isLinked);

        if (isLinked == GL_FALSE)
        {
            GLint maxLength{0};

            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH,
                           &maxLength);

            Vector<GLchar> infoLog(maxLength);

            glGetProgramInfoLog(m_programID, maxLength,
                                &maxLength, &infoLog[0]);

            glDeleteProgram(m_programID);

            glDeleteShader(vertexShader);

            glDeleteShader(fragmentShader);

            return;
        }

        glDetachShader(m_programID, vertexShader);

        glDetachShader(m_programID, fragmentShader);

        glDeleteShader(vertexShader);

        glDeleteShader(fragmentShader);
    }

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

    void ShaderProgram::Cleanup()
    {
        glDeleteProgram(m_programID);
    }
}