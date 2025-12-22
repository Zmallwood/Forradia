/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

// - Consider implementing LRU eviction of operations memory, which is used when the operations
// cache reaches a certain limit.

#include "Image2DRenderer.hpp"
#include "SDLDevice.hpp"

namespace Forradia {
    auto Image2DRenderer::DrawImageByTextureID(int uniqueRenderID, GLuint textureID, float xPos,
                                               float yPos, float width, float height,
                                               bool updateExisting) -> void {
        this->SetupState();

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto needFillBuffers{false};
        auto canvasSize{GetCanvasSize(SDLDevice::Instance().GetWindow())};

        auto xPx{static_cast<int>(xPos * canvasSize.width)};
        auto yPx{static_cast<int>(yPos * canvasSize.height)};
        auto widthPx{static_cast<int>(width * canvasSize.width)};
        auto heightPx{static_cast<int>(height * canvasSize.height)};

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

            Image2DRenderingOperation entry;
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
            float vertices[] = {xPos,         yPos,          0.0F, 1.0F, 1.0F, 1.0F, 0.0F, 0.0F,
                                xPos + width, yPos,          0.0F, 1.0F, 1.0F, 1.0F, 1.0F, 0.0F,
                                xPos + width, yPos + height, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                                xPos,         yPos + height, 0.0F, 1.0F, 1.0F, 1.0F, 0.0F, 1.0F};

            unsigned short indices[]{0, 1, 2, 3};

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * k_indicesCount, indices,
                         GL_DYNAMIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 8 * k_verticesCount, vertices,
                         GL_DYNAMIC_DRAW);

            this->SetupAttributeLayout();
        }

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLE_FAN, k_indicesCount, GL_UNSIGNED_SHORT, nullptr);

        this->RestoreState();
    }
}
