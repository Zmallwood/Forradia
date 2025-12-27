/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

// - Consider change to using LRU eviction of operations memory, which is used when the operations
// cache reaches a certain limit.

#include "Color2DRenderer.hpp"
#include <array>
#include <vector>

namespace ForradiaEngine
{
    auto Color2DRenderer::drawLine(int uniqueRenderID, Color color, float xPos1, float yPos1,
                                   float xPos2, float yPos2, float lineWidth, bool updateExisting)
        -> void
    {
        this->setupState();

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto needFillBuffers{false};

        // If the operation is cached, use the cached operation.
        if (this->drawingOperationIsCached(uniqueRenderID))
        {
            auto &entry = m_operationsCache.at(uniqueRenderID);

            vao = entry.vao;
            ibo = entry.ibo;
            vbo = entry.vbo;

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        }
        else
        {
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

        constexpr auto k_indicesCount{4};

        // If the buffers need to be filled or the operation is being updated, fill the buffers.
        if (needFillBuffers || updateExisting)
        {
            constexpr auto k_verticesCount{4};

            auto xPos{xPos1};
            auto yPos{yPos1};

            float width;
            float height;

            if (xPos2 - xPos1 > yPos2 - yPos1)
            {
                width = xPos2 - xPos1;
                height = lineWidth;
                // NOLINTNEXTLINE(readability-magic-numbers)
                yPos -= height / 2.0F;
            }
            else
            {
                width = lineWidth;
                height = yPos2 - yPos1;
                // NOLINTNEXTLINE(readability-magic-numbers)
                xPos -= width / 2.0F;
            }

            std::vector<float> vertices;

            vertices = {xPos,         yPos,          0.0F, color.r, color.g, color.b, color.a,
                        xPos + width, yPos,          0.0F, color.r, color.g, color.b, color.a,
                        xPos + width, yPos + height, 0.0F, color.r, color.g, color.b, color.a,
                        xPos,         yPos + height, 0.0F, color.r, color.g, color.b, color.a};

            std::array<unsigned short, 4> indices{0, 1, 2, 3};

            constexpr int k_floatsPerVertex = 7;

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * k_indicesCount,
                         indices.data(), GL_DYNAMIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * k_floatsPerVertex * k_verticesCount,
                         vertices.data(), GL_DYNAMIC_DRAW);

            this->setupAttributeLayout();
        }

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glDrawElements(GL_TRIANGLE_FAN, k_indicesCount, GL_UNSIGNED_SHORT, nullptr);

        Color2DRenderer::restoreState();
    }
}
