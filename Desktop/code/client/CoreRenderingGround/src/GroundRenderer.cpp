/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GroundRenderer.hpp"
#include "SDLDevice.hpp"
#include "ShaderProgram.hpp"

namespace Forradia {
void GroundRenderer::Cleanup() {
  for (auto &entry : m_operationsCache) {
    glDeleteBuffers(1, &entry.second.ibo);
    glDeleteBuffers(1, &entry.second.vbo);
    glDeleteVertexArrays(1, &entry.second.vao);
  }
  m_operationsCache.clear();
}

void GroundRenderer::SetupState() const {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CW);

  auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};

  glViewport(0, 0, canvasSize.width, canvasSize.height);
  glUseProgram(GetShaderProgram()->GetProgramID());
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GroundRenderer::RestoreState() const {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);
}

void GroundRenderer::Reset() {
  this->Cleanup();
}

void GroundRenderer::SetupAttributeLayout() const {
  // Set up the attribute layout for the vertex shader.

  // Position.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void *)(sizeof(float) * 0));
  glEnableVertexAttribArray(0);

  // Color.
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  // Texture coordinates.
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void *)(sizeof(float) * 6));
  glEnableVertexAttribArray(2);

  // Normals.
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void *)(sizeof(float) * 8));
  glEnableVertexAttribArray(3);
}

bool GroundRenderer::DrawingOperationIsCached(int uniqueRenderID) const {
  return m_operationsCache.contains(uniqueRenderID);
}

void GroundRenderer::InitializeDerived() {
  m_layoutLocationMVP = glGetUniformLocation(GetShaderProgram()->GetProgramID(), "MVP");
}
}