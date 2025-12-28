/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ShaderProgram.hpp"
#include <vector>

namespace ForradiaEngine
{
    auto ShaderProgram::initialize(std::string_view vertexShaderSource,
                                   std::string_view fragmentShaderSource) -> void
    {
        auto vertexShader{ShaderProgram::getShader(vertexShaderSource, GL_VERTEX_SHADER)};

        // If the vertex shader failed.
        if (0 == vertexShader)
        {
            glDeleteShader(vertexShader);

            return;
        }

        auto fragmentShader{ShaderProgram::getShader(fragmentShaderSource, GL_FRAGMENT_SHADER)};

        // If the fragment shader failed.
        if (0 == fragmentShader)
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            return;
        }

        auto isLinked{this->createProgram(vertexShader, fragmentShader)};

        // If the link failed, dont continue.
        if (GL_FALSE == isLinked)
        {
            return;
        }

        glDetachShader(m_programID, vertexShader);
        glDetachShader(m_programID, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    auto ShaderProgram::cleanup() -> void
    {
        glDeleteProgram(m_programID);
        m_programID = 0;
    }

    auto ShaderProgram::getShader(std::string_view shaderSource, int shaderType) -> GLuint
    {
        auto shader{glCreateShader(shaderType)};
        const auto *source{(const GLchar *)shaderSource.data()};

        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint isCompiled{0};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

        // If the compile failed.
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength{0};
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

            return 0;
        }

        return shader;
    }

    auto ShaderProgram::createProgram(GLuint vertexShader, GLuint fragmentShader) -> GLint
    {
        m_programID = glCreateProgram();
        glAttachShader(m_programID, vertexShader);
        glAttachShader(m_programID, fragmentShader);
        glLinkProgram(m_programID);

        GLint isLinked{0};
        glGetProgramiv(m_programID, GL_LINK_STATUS, static_cast<int *>(&isLinked));

        // If the link failed.
        if (isLinked == GL_FALSE)
        {
            GLint maxLength{0};
            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_programID, maxLength, &maxLength, infoLog.data());

            glDeleteProgram(m_programID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        return isLinked;
    }
}
