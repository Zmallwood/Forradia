/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Image2DRenderer.hpp"
    #include "ForradiaEngine/Common/Utilities/CanvasUtilities.hpp"
    #include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
    #include "ForradiaEngine/Rendering/Base/ShaderProgram.hpp"
// clang-format on

namespace Forradia
{
    auto Image2DRenderer::cleanup() const -> void
    {
        for (const auto &val : m_operationsCache | std::views::values)
        {
            glDeleteBuffers(1, &val.ibo);
            glDeleteBuffers(1, &val.vbo);
            glDeleteVertexArrays(1, &val.vao);
        }
    }

    auto Image2DRenderer::setupState() const -> void
    {
        auto canvasSize{getCanvasSize(SDLDevice::instance().getWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);
        glUseProgram(getShaderProgram()->getProgramID());
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    auto Image2DRenderer::restoreState() -> void
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glUseProgram(0);
    }

    auto Image2DRenderer::setupAttributeLayout() const -> void
    {
        constexpr int k_stride{8};
        constexpr int k_posPos{0};
        constexpr int k_colorPos{3};
        constexpr int k_uvPos{6};

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              reinterpret_cast<void *>(sizeof(float) * k_posPos));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              reinterpret_cast<void *>(sizeof(float) * k_colorPos));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              reinterpret_cast<void *>(sizeof(float) * k_uvPos));
        glEnableVertexAttribArray(2);
    }

    auto Image2DRenderer::drawingOperationIsCached(int uniqueRenderID) const -> bool
    {
        return m_operationsCache.contains(uniqueRenderID);
    }
}
