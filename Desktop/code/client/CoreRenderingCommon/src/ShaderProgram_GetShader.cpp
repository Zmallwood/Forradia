/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ShaderProgram.hpp"
#include <GL/glext.h>
#include <vector>

namespace Forradia
{
    auto ShaderProgram::GetShader(std::string_view shaderSource, int shaderType) -> GLuint
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
}
