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
        int uniqueRenderID, GLuint textureID, float x,
        float y, float width, float height,
        bool useOperationsCache, bool updateExisting)
    {
        // Setup state.

        this->SetupState();

        // To store the vertex array object, index buffer
        // object and vertex buffer object.

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        // To store whether the buffers need to be filled.

        auto needFillBuffers{false};

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        // Convert the coordinates to pixel coordinates.

        auto xPx{CInt(x * canvasSize.width)};
        auto yPx{CInt(y * canvasSize.height)};
        auto widthPx{CInt(width * canvasSize.width)};
        auto heightPx{CInt(height * canvasSize.height)};

        // If the operation is cached, use the cached
        // operation.

        // TODO: Implement LRU eviction of operations
        // memory, which is used when the operations cache
        // reaches a certain limit.

        if (useOperationsCache &&
            this->DrawingOperationIsCached(uniqueRenderID))
        {
            // Get the cached operation.

            auto &entry =
                m_operationsCache.at(uniqueRenderID);

            // Set the vertex array object, index buffer
            // object and vertex buffer object.

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            // Bind the vertex array object, index buffer
            // object and vertex buffer object.

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

        const auto k_verticesCount{4};

        const auto k_indicesCount{4};

        if (needFillBuffers || updateExisting)
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

            unsigned short indices[]{0, 1, 2, 3};

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