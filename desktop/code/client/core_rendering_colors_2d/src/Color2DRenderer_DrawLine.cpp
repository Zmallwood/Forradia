//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Color2DRenderer.hpp"

#include "ShaderProgram.hpp"

#include <cmath>

namespace Forradia
{
    void Color2DRenderer::DrawLine(int uniqueRenderID, Color color, float x1, float y1, float x2,
                                   float y2, float lineWidth, bool updateExisting)
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

        const auto k_verticesCount{4};

        const auto k_indicesCount{4};

        // If the buffers need to be filled or the operation is being updated, fill the buffers.

        if (needFillBuffers || updateExisting)
        {
            auto &c{color};

            // Calculate the line direction vector.

            auto dx{x2 - x1};
            auto dy{y2 - y1};

            // Calculate the length of the line.

            auto length{std::sqrt(dx * dx + dy * dy)};

            // Calculate the perpendicular vector (normalized) for the line width.
            // Perpendicular to (dx, dy) is (-dy, dx) or (dy, -dx).
            // We'll use (-dy, dx) normalized.

            auto halfWidth{lineWidth * 0.5f};

            float perpX{0.0f};
            float perpY{0.0f};

            if (length > 0.0001f)
            {
                // Normalize the perpendicular vector and scale by half width.

                perpX = (-dy / length) * halfWidth;
                perpY = (dx / length) * halfWidth;
            }
            else
            {
                // If the line has zero length, use a default perpendicular vector.
                // Use a small default width direction.

                perpX = halfWidth;
                perpY = 0.0f;
            }

            // Calculate the four corners of the line quad.
            // The quad is formed by offsetting the start and end points
            // perpendicular to the line direction.

            auto x1Top{x1 + perpX};
            auto y1Top{y1 + perpY};
            auto x1Bottom{x1 - perpX};
            auto y1Bottom{y1 - perpY};

            auto x2Top{x2 + perpX};
            auto y2Top{y2 + perpY};
            auto x2Bottom{x2 - perpX};
            auto y2Bottom{y2 - perpY};

            // Define the vertices and indices.

            // clang-format off

            float vertices[] = {
                x1Bottom,   y1Bottom,   0.0f,
                c.r,        c.g,        c.b,    c.a,
                x1Top,      y1Top,      0.0f,
                c.r,        c.g,        c.b,    c.a,
                x2Top,      y2Top,      0.0f,
                c.r,        c.g,        c.b,    c.a,
                x2Bottom,   y2Bottom,   0.0f,
                c.r,        c.g,        c.b,    c.a
            };

            // clang-format on

            unsigned short indices[]{0, 1, 2, 3};

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

        // Draw the line as a quad using triangle fan.

        glDrawElements(GL_TRIANGLE_FAN, k_indicesCount, GL_UNSIGNED_SHORT, nullptr);

        // Restore the state.

        this->RestoreState();
    }
}
