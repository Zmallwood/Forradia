//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "ShaderProgram.hpp"

namespace Forradia {
    void ShaderProgram::Initialize(StringView vertexShaderSource, StringView fragmentShaderSource) {
        // Create the vertex shader program.
        auto vertexShader{this->GetShader(vertexShaderSource, GL_VERTEX_SHADER)};

        // If the vertex shader failed.
        if (0 == vertexShader) {
            // Cleanup and dont continue.
            glDeleteShader(vertexShader);

            return;
        }

        // Create the fragment shader program.
        auto fragmentShader{this->GetShader(fragmentShaderSource, GL_FRAGMENT_SHADER)};

        // If the fragment shader failed.
        if (0 == fragmentShader) {
            // Cleanup and dont continue.

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            return;
        }

        // Create the linked shader program.
        auto isLinked{this->CreateProgram(vertexShader, fragmentShader)};

        // If the link failed, dont continue.
        if (GL_FALSE == isLinked) {
            return;
        }

        // Cleanup.

        glDetachShader(m_programID, vertexShader);
        glDetachShader(m_programID, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void ShaderProgram::Cleanup() {
        // Delete the program.
        glDeleteProgram(m_programID);

        // Reset the program ID.
        m_programID = 0;
    }
}