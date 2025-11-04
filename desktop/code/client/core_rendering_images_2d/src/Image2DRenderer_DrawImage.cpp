//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Image2DRenderer.hpp"

#include "ShaderProgram.hpp"

#include "SDLDevice.hpp"

namespace Forradia
{
    void Image2DRenderer::DrawImageByTextureID(
        GLuint textureID, float x, float y, float width,
        float height, bool useOperationsMemory)
    {
        this->SetupState();

        unsigned short indices[]{0, 1, 2, 3};

        const auto k_verticesCount{4};

        const auto k_indicesCount{4};

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto needFillBuffers{false};

        // TODO: Implement LRU eviction of operations
        // memory, which is used when the operations cache
        // reaches a certain limit.

        if (useOperationsMemory &&
            m_operationsCache.contains(x) &&
            m_operationsCache.at(x).contains(y) &&
            m_operationsCache.at(x).at(y).contains(
                textureID))
        {
            auto &entry =
                m_operationsCache.at(x).at(y).at(textureID);

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            // TODO: Consider using epsilon-based comparions
            // for float values below.

            if (x != entry.x || y != entry.y ||
                width != entry.width ||
                height != entry.height)
            {
                needFillBuffers = true;

                entry.x = x;

                entry.y = y;

                entry.width = width;

                entry.height = height;
            }
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

            entry.x = x;

            entry.y = y;

            entry.width = width;

            entry.height = height;

            m_operationsCache[x][y][textureID] = entry;

            needFillBuffers = true;
        }

        if (needFillBuffers)
        {
            float vertices[] = {
                x,         y,          0.0f, 1.0f,
                1.0f,      1.0f,       0.0,  0.0,
                x + width, y,          0.0f, 1.0f,
                1.0f,      1.0f,       1.0,  0.0,
                x + width, y + height, 0.0f, 1.0f,
                1.0f,      1.0f,       1.0,  1.0,
                x,         y + height, 0.0f, 1.0f,
                1.0f,      1.0f,       0.0,  1.0};

            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(indices[0]) *
                             k_indicesCount,
                         indices, GL_DYNAMIC_DRAW);

            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(vertices[0]) * 8 *
                             k_verticesCount,
                         vertices, GL_DYNAMIC_DRAW);

            this->SetupAttributeLayout();
        }

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLE_FAN, k_indicesCount,
                       GL_UNSIGNED_SHORT, nullptr);

        this->ResetState();
    }
}