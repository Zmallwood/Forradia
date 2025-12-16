//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "Color2DRenderer.hpp"
#include "SDLDevice.hpp"
#include "ShaderProgram.hpp"

namespace Forradia {
void Color2DRenderer::Cleanup() {
  for (auto &entry : m_operationsCache) {
    glDeleteBuffers(1, &entry.second.ibo);
    glDeleteBuffers(1, &entry.second.vbo);
    glDeleteVertexArrays(1, &entry.second.vao);
  }
  m_operationsCache.clear();
}

void Color2DRenderer::SetupState() const {
  auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};

  glViewport(0, 0, canvasSize.width, canvasSize.height);
  glUseProgram(GetShaderProgram()->GetProgramID());
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Color2DRenderer::RestoreState() const {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glUseProgram(0);
}

void Color2DRenderer::SetupAttributeLayout() const {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void *)(sizeof(float) * 0));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);
}

bool Color2DRenderer::DrawingOperationIsCached(int uniqueRenderID) const {
  return m_operationsCache.contains(uniqueRenderID);
}
}