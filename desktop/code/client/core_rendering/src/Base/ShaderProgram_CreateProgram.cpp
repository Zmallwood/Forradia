//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ShaderProgram.hpp"

namespace Forradia
{
    GLint
    ShaderProgram::CreateProgram(GLuint vertexShader,
                                 GLuint fragmentShader)
    {
        // Create a new shader program.

        m_programID = glCreateProgram();

        // Attach the vertex and fragment shaders to
        // the program.

        glAttachShader(m_programID, vertexShader);

        glAttachShader(m_programID, fragmentShader);

        // Link the program.

        glLinkProgram(m_programID);

        // Get the link status.

        GLint isLinked{0};

        glGetProgramiv(m_programID, GL_LINK_STATUS,
                       (int *)&isLinked);

        // If the link failed.

        if (isLinked == GL_FALSE)
        {
            // Get the length of the info log.

            GLint maxLength{0};

            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH,
                           &maxLength);

            // Get the info log.

            Vector<GLchar> infoLog(maxLength);

            glGetProgramInfoLog(m_programID, maxLength,
                                &maxLength, &infoLog[0]);

            // Delete the program.

            glDeleteProgram(m_programID);

            // Delete the shaders.

            glDeleteShader(vertexShader);

            glDeleteShader(fragmentShader);
        }

        // Return the link status.

        return isLinked;
    }
}