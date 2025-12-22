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

    auto Image2DRenderer::RestoreState() const -> void {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glUseProgram(0);
    }

    auto Image2DRenderer::SetupAttributeLayout() const -> void {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                              (void *)(sizeof(float) * 0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                              (void *)(sizeof(float) * 3));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                              (void *)(sizeof(float) * 6));
        glEnableVertexAttribArray(2);
    }

    auto Image2DRenderer::DrawingOperationIsCached(int uniqueRenderID) const -> bool {
        return m_operationsCache.contains(uniqueRenderID);
    }
}
