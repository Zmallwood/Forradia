/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "ModelRenderer.hpp"
#include "SDLDevice.hpp"
#include "ShaderProgram.hpp"

namespace Forradia {
void ModelRenderer::Cleanup() {
  for (auto &entry : m_operationsCache) {
    glDeleteBuffers(1, &entry.second.ibo);
    glDeleteBuffers(1, &entry.second.vbo);
    glDeleteVertexArrays(1, &entry.second.vao);
  }
  m_operationsCache.clear();
}

void ModelRenderer::SetupState() const {
  glEnable(GL_DEPTH_TEST);

  auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};

  glViewport(0, 0, canvasSize.width, canvasSize.height);
  glUseProgram(GetShaderProgram()->GetProgramID());
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
}

void ModelRenderer::RestoreState() const {
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisable(GL_DEPTH_TEST);
}

void ModelRenderer::SetupAttributeLayout() const {
  // Setup the attribute layout.

  // Position.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(sizeof(float) * 0));
  glEnableVertexAttribArray(0);

  // Normal.
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  // Texture coordinates (UV coordinates).
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(sizeof(float) * 6));
  glEnableVertexAttribArray(2);
}

bool ModelRenderer::DrawingOperationIsCached(int modelNameHash) const {
  // Check if the drawing operation is cached.
  //
  // Note: For this renderer the modelNameHash can be used as a key since what changes
  // between different rendering operations is the model matrix, not the vertex data
  // (which is the case for the other renderers).
  return m_operationsCache.contains(modelNameHash);
}

void ModelRenderer::InitializeDerived() {
  // Obtain the layout location for the uniform matrices.

  m_layoutLocationProjectionMatrix =
      glGetUniformLocation(GetShaderProgram()->GetProgramID(), "projection");
  m_layoutLocationViewMatrix = glGetUniformLocation(GetShaderProgram()->GetProgramID(), "view");
  m_layoutLocationModelMatrix = glGetUniformLocation(GetShaderProgram()->GetProgramID(), "model");
}
}