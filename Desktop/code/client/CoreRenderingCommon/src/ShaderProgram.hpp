/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/**
 * Shader program which is used for each renderer.
 */
class ShaderProgram {
 public:
  /**
   * Initialize the shader program.
   *
   * @param vertexShaderSource Vertex shader source.
   * @param fragmentShaderSource Fragment shader source.
   */
  ShaderProgram(StringView vertexShaderSource, StringView fragmentShaderSource) {
    this->Initialize(vertexShaderSource, fragmentShaderSource);
  }

  /**
   * Cleanup the shader program.
   */
  ~ShaderProgram() {
    this->Cleanup();
  }

  /**
   * Get the program ID.
   *
   * @return The program ID.
   */
  auto GetProgramID() const {
    return m_programID;
  }

 private:
  void Initialize(StringView vertexShaderSource, StringView fragmentShaderSource);

  void Cleanup();

  GLuint GetShader(StringView shaderSource, int shaderType) const;

  GLint CreateProgram(GLuint vertexShader, GLuint fragmentShader);

  GLuint m_programID;
};
}