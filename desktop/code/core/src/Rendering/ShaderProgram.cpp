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
        GLuint vertexShader{
            glCreateShader(GL_VERTEX_SHADER)};

        const GLchar *source{
            (const GLchar *)vertexShaderSource.data()};

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

            glDeleteShader(vertexShader);

            return;
        }

        GLuint fragmentShader{
            glCreateShader(GL_FRAGMENT_SHADER)};

        source =
            (const GLchar *)fragmentShaderSource.data();

        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,
                      &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength{0};

            glGetShaderiv(fragmentShader,
                          GL_INFO_LOG_LENGTH, &maxLength);

            Vector<GLchar> infoLog(maxLength);

            glGetShaderInfoLog(fragmentShader, maxLength,
                               &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);

            glDeleteShader(vertexShader);

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

    void ShaderProgram::Cleanup()
    {
        glDeleteProgram(m_programID);
    }
}