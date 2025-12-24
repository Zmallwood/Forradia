/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ModelRenderer.hpp"
#include "CanvasUtilities.hpp"
#include "GraphicsDevices/SDLDevice.hpp"
#include "Rendering/Base/ShaderProgram.hpp"

namespace Forradia
{
    auto ModelRenderer::cleanup() -> void
    {
        for (auto &val : m_operationsCache | std::views::values)
        {
            glDeleteBuffers(1, &val.ibo);
            glDeleteBuffers(1, &val.vbo);
            glDeleteVertexArrays(1, &val.vao);
        }

        m_operationsCache.clear();
    }

    auto ModelRenderer::setupState() const -> void
    {
        glEnable(GL_DEPTH_TEST);

        auto canvasSize{getCanvasSize(SDLDevice::instance().getWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);
        glUseProgram(dynamic_cast<const RendererBase *>(this)->getShaderProgram()->getProgramID());
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
    }

    auto ModelRenderer::restoreState() -> void
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisable(GL_DEPTH_TEST);
    }

    auto ModelRenderer::setupAttributeLayout() const -> void
    {
        // Set up the attribute layout.

        constexpr int k_stride{8};
        constexpr int k_posPos{0};
        constexpr int k_normalPos{3};
        constexpr int k_uvPos{6};

        // Position.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              reinterpret_cast<void *>(sizeof(float) * k_posPos));
        glEnableVertexAttribArray(0);

        // Normal.
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              reinterpret_cast<void *>(sizeof(float) * k_normalPos));
        glEnableVertexAttribArray(1);

        // Texture coordinates (UV coordinates).
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              reinterpret_cast<void *>(sizeof(float) * k_uvPos));
        glEnableVertexAttribArray(2);
    }

    auto ModelRenderer::drawingOperationIsCached(int modelNameHash) const -> bool
    {
        // Check if the drawing operation is cached.
        //
        // Note: For this renderer the modelNameHash can be used as a key since what changes
        // between different rendering operations is the model matrix, not the vertex data
        // (which is the case for the other renderers).
        return m_operationsCache.contains(modelNameHash);
    }

    auto ModelRenderer::initializeDerived() -> void
    {
        // Obtain the layout location for the uniform matrices.

        m_layoutLocationProjectionMatrix = glGetUniformLocation(
            dynamic_cast<const RendererBase *>(this)->getShaderProgram()->getProgramID(),
            "projection");
        m_layoutLocationViewMatrix = glGetUniformLocation(
            dynamic_cast<const RendererBase *>(this)->getShaderProgram()->getProgramID(), "view");
        m_layoutLocationModelMatrix = glGetUniformLocation(
            dynamic_cast<const RendererBase *>(this)->getShaderProgram()->getProgramID(), "model");
    }
}
