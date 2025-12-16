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
  auto vertexShader{this->GetShader(vertexShaderSource, GL_VERTEX_SHADER)};

  // If the vertex shader failed.
  if (0 == vertexShader) {
    glDeleteShader(vertexShader);
    return;
  }

  auto fragmentShader{this->GetShader(fragmentShaderSource, GL_FRAGMENT_SHADER)};

  // If the fragment shader failed.
  if (0 == fragmentShader) {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return;
  }

  auto isLinked{this->CreateProgram(vertexShader, fragmentShader)};

  // If the link failed, dont continue.
  if (GL_FALSE == isLinked) {
    return;
  }

  glDetachShader(m_programID, vertexShader);
  glDetachShader(m_programID, fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void ShaderProgram::Cleanup() {
  glDeleteProgram(m_programID);
  m_programID = 0;
}
}