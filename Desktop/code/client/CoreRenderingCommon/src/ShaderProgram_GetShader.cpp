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
  auto shader{glCreateShader(shaderType)};
  const auto *source{(const GLchar *)shaderSource.data()};

  glShaderSource(shader, 1, &source, 0);
  glCompileShader(shader);
  GLint isCompiled{0};
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

  // If the compile failed.
  if (isCompiled == GL_FALSE) {
    GLint maxLength{0};
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    Vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
    return 0;
  }

  return shader;
}
}