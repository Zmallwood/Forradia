/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Image2DRenderer.hpp"
#include "SDLDevice.hpp"
#include "ShaderProgram.hpp"

namespace Forradia {
    auto Image2DRenderer::Cleanup() -> void {
        for (auto &entry : m_operationsCache) {
            glDeleteBuffers(1, &entry.second.ibo);
            glDeleteBuffers(1, &entry.second.vbo);
            glDeleteVertexArrays(1, &entry.second.vao);
        }
    }

    auto Image2DRenderer::SetupState() const -> void {
        auto canvasSize{GetCanvasSize(SDLDevice::Instance().GetWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);
        glUseProgram(GetShaderProgram()->GetProgramID());
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    auto Image2DRenderer::RestoreState() -> void {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glUseProgram(0);
    }

    auto Image2DRenderer::SetupAttributeLayout() const -> void {
        constexpr int k_stride{8};
        constexpr int k_posPos{0};
        constexpr int k_colorPos{3};
        constexpr int k_uvPos{6};

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              (void *)(sizeof(float) * k_posPos));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              (void *)(sizeof(float) * k_colorPos));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              (void *)(sizeof(float) * k_uvPos));
        glEnableVertexAttribArray(2);
    }

    auto Image2DRenderer::DrawingOperationIsCached(int uniqueRenderID) const -> bool {
        return m_operationsCache.contains(uniqueRenderID);
    }
}
