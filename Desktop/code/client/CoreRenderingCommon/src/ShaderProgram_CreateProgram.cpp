/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ShaderProgram.hpp"
#include <GL/glext.h>
#include <vector>

namespace Forradia
{
    auto ShaderProgram::CreateProgram(GLuint vertexShader, GLuint fragmentShader) -> GLint
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
