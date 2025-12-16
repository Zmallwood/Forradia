/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Image2DRenderer.hpp"
#include "SDLDevice.hpp"
#include "ShaderProgram.hpp"

namespace Forradia {
void Image2DRenderer::Cleanup() {
  for (auto &entry : m_operationsCache) {
    glDeleteBuffers(1, &entry.second.ibo);
    glDeleteBuffers(1, &entry.second.vbo);
    glDeleteVertexArrays(1, &entry.second.vao);
  }
}

void Image2DRenderer::SetupState() const {
  auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};

  glViewport(0, 0, canvasSize.width, canvasSize.height);
  glUseProgram(GetShaderProgram()->GetProgramID());
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Image2DRenderer::RestoreState() const {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glUseProgram(0);
}

void Image2DRenderer::SetupAttributeLayout() const {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(sizeof(float) * 0));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(sizeof(float) * 6));
  glEnableVertexAttribArray(2);
}

bool Image2DRenderer::DrawingOperationIsCached(int uniqueRenderID) const {
  return m_operationsCache.contains(uniqueRenderID);
}
}