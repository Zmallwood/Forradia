//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Color2DRenderer.hpp"

#include "ShaderProgram.hpp"

namespace Forradia
{
    void Color2DRenderer::DrawLine(int uniqueRenderID, Color color, float x1, float y1, float x2,
                                   float y2, bool updateExisting)
    {
        // Setup state.

        this->SetupState();

        // To store the vertex array object, index buffer object and vertex buffer object.

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        // To store whether the buffers need to be filled.

        auto needFillBuffers{false};

        // If the operation is cached, use the cached operation.

        // TODO: Implement LRU eviction of operations memory, which is used when the operations
        // cache reaches a certain limit.

        if (this->DrawingOperationIsCached(uniqueRenderID))
        {
            // Get the cached operation.

            auto &entry = m_operationsCache.at(uniqueRenderID);

            // Set the vertex array object, index buffer object and vertex buffer object.

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            // Bind the vertex array object, index buffer object and vertex buffer object.

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        }
        else
        {
            // Generate the vertex array object, index buffer object and vertex buffer object.

            glGenVertexArrays(1, &vao);

            glGenBuffers(1, &vbo);

            glGenBuffers(1, &ibo);

            // Bind the vertex array object, index buffer object and vertex buffer object.

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            // Create a new rendering operation and cache it.

            Color2DRenderingOperation entry;

            entry.vao = vao;

            entry.ibo = ibo;

            entry.vbo = vbo;

            m_operationsCache[uniqueRenderID] = entry;

            // Set the need to fill the buffers to true.

            needFillBuffers = true;
        }

        // To store the number of vertices and indices.

        const auto k_verticesCount{2};

        const auto k_indicesCount{2};

        // If the buffers need to be filled or the operation is being updated, fill the buffers.

        if (needFillBuffers || updateExisting)
        {
            auto &c{color};

            // Define the vertices and indices.

            // clang-format off

            float vertices[] = {
                x1,     y1,     0.0f,
                c.r,    c.g,     c.b,    c.a,
                x2,     y2,     0.0f,
                c.r,    c.g,     c.b,    c.a
            };

            // clang-format on

            unsigned short indices[]{0, 1};

            // Fill the index buffer.

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * k_indicesCount, indices,
                         GL_DYNAMIC_DRAW);

            // Fill the vertex buffer.

            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 7 * k_verticesCount, vertices,
                         GL_DYNAMIC_DRAW);

            // Setup the attribute layout.

            this->SetupAttributeLayout();
        }

        // Bind the vertex array object, index buffer object and vertex buffer object.

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        // Draw the line.

        glDrawElements(GL_LINES, k_indicesCount, GL_UNSIGNED_SHORT, nullptr);

        // Restore the state.

        this->RestoreState();
    }
}
