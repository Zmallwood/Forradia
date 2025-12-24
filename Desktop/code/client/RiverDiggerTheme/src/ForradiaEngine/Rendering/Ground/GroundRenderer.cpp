/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GroundRenderer.hpp"
#include "ForradiaEngine/Common/Utilities/CanvasUtilities.hpp"
#include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
#include "ForradiaEngine/Rendering/Base/ShaderProgram.hpp"

namespace Forradia
{
    auto GroundRenderer::cleanup() -> void
    {
        for (auto &entry : m_operationsCache)
        {
            glDeleteBuffers(1, &entry.second.ibo);
            glDeleteBuffers(1, &entry.second.vbo);
            glDeleteVertexArrays(1, &entry.second.vao);
        }

        m_operationsCache.clear();
    }

    auto GroundRenderer::setupState() const -> void
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        auto canvasSize{getCanvasSize(SDLDevice::instance().getWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);
        glUseProgram(dynamic_cast<const RendererBase *>(this)->getShaderProgram()->getProgramID());
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    auto GroundRenderer::restoreState() -> void
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
    }

    auto GroundRenderer::reset() -> void
    {
        this->cleanup();
    }

    auto GroundRenderer::setupAttributeLayout() const -> void
    {
        // Set up the attribute layout for the vertex shader.

        constexpr int k_stride{11};
        constexpr int k_positionPosition{0};
        constexpr int k_positionColor{3};
        constexpr int k_positionUVs{6};
        constexpr int k_positionNormals{8};

        // Position.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              (void *)(sizeof(float) * k_positionPosition));
        glEnableVertexAttribArray(0);

        // Color.
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              (void *)(sizeof(float) * k_positionColor));
        glEnableVertexAttribArray(1);

        // Texture coordinates.
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              (void *)(sizeof(float) * k_positionUVs));
        glEnableVertexAttribArray(2);

        // Normals.
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              (void *)(sizeof(float) * k_positionNormals));
        glEnableVertexAttribArray(3);
    }

    auto GroundRenderer::drawingOperationIsCached(int uniqueRenderID) const -> bool
    {
        return m_operationsCache.contains(uniqueRenderID);
    }

    auto GroundRenderer::initializeDerived() -> void
    {
        m_layoutLocationMVP = glGetUniformLocation(
            dynamic_cast<const RendererBase *>(this)->getShaderProgram()->getProgramID(), "MVP");
    }
}
