/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

// - Consider implementing LRU eviction of operations memory, which is used when the operations
// cache reaches a certain limit.

/* Includes */ // clang-format off
    #include "Image2DRenderer.hpp"
    
    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <array>
// clang-format on

namespace ForradiaEngine
{
    auto Image2DRenderer::drawImageByTextureID(int uniqueRenderID, GLuint textureID, float xPos,
                                               float yPos, float width, float height,
                                               bool updateExisting) -> void
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

            Image2DRenderingOperation entry;
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
            constexpr int k_numFloatsForVerticesData{32};

            std::array<float, k_numFloatsForVerticesData> vertices = {
                xPos,         yPos,          0.0F, 1.0F, 1.0F, 1.0F, 0.0F, 0.0F,
                xPos + width, yPos,          0.0F, 1.0F, 1.0F, 1.0F, 1.0F, 0.0F,
                xPos + width, yPos + height, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                xPos,         yPos + height, 0.0F, 1.0F, 1.0F, 1.0F, 0.0F, 1.0F};

            std::array<unsigned short, 4> indices{0, 1, 2, 3};

            constexpr int k_floatsPerVertex{8};

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * k_indicesCount,
                         indices.data(), GL_DYNAMIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * k_floatsPerVertex * k_verticesCount,
                         vertices.data(), GL_DYNAMIC_DRAW);

            this->setupAttributeLayout();
        }

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLE_FAN, k_indicesCount, GL_UNSIGNED_SHORT, nullptr);

        Image2DRenderer::restoreState();
    }
}
