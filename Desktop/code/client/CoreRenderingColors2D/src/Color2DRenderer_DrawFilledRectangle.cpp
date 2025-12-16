//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:
// - Consider change to using LRU eviction of operations memory, which is used when the operations
// cache reaches a certain limit.

#include "Color2DRenderer.hpp"
#include "SDLDevice.hpp"

namespace Forradia {
void Color2DRenderer::DrawFilledRectangle(int uniqueRenderID, Color color, float x, float y,
                                          float width, float height, bool updateExisting) {
  this->SetupState();

  GLuint vao;
  GLuint ibo;
  GLuint vbo;

  auto needFillBuffers{false};

  // If the operation is cached, use the cached operation.
  if (this->DrawingOperationIsCached(uniqueRenderID)) {
    auto &entry = m_operationsCache.at(uniqueRenderID);

    vao = entry.vao;
    ibo = entry.ibo;
    vbo = entry.vbo;

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  } else {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    Color2DRenderingOperation entry;
    entry.vao = vao;
    entry.ibo = ibo;
    entry.vbo = vbo;
    m_operationsCache[uniqueRenderID] = entry;

    needFillBuffers = true;
  }

  const auto k_verticesCount{4};
  const auto k_indicesCount{4};

  // If the buffers need to be filled or the operation is being updated, fill the buffers.
  if (needFillBuffers || updateExisting) {
    auto &c{color};

    // clang-format off
            float vertices[] = {
                x,          y,              0.0f,
                c.r,        c.g,            c.b,    c.a,
                x + width,  y,              0.0f,
                c.r,        c.g,            c.b,    c.a,
                x + width,  y + height,     0.0f,
                c.r,        c.g,            c.b,    c.a,
                x,          y + height,     0.0f,
                c.r,        c.g,            c.b,    c.a
            };
    // clang-format on

    unsigned short indices[]{0, 1, 2, 3};

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * k_indicesCount, indices,
                 GL_DYNAMIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 7 * k_verticesCount, vertices,
                 GL_DYNAMIC_DRAW);

    this->SetupAttributeLayout();
  }

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

  glDrawElements(GL_TRIANGLE_FAN, k_indicesCount, GL_UNSIGNED_SHORT, nullptr);

  this->RestoreState();
}
}