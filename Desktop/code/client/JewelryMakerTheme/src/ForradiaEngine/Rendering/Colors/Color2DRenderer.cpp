/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Color2DRenderer.hpp"
    
    #include "ForradiaEngine/Common/Utilities.hpp"
    #include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
    #include "ForradiaEngine/Rendering/Base/ShaderProgram.hpp"
    #include <GL/glew.h>
    #include <GL/gl.h>
// clang-format on

namespace ForradiaEngine
{
    auto Color2DRenderer::cleanup() -> void
    {
        for (auto &val : m_operationsCache | std::views::values)
        {
            glDeleteBuffers(1, &val.ibo);
            glDeleteBuffers(1, &val.vbo);
            glDeleteVertexArrays(1, &val.vao);
        }

        m_operationsCache.clear();
    }

    auto Color2DRenderer::setupState() const -> void
    {
        auto canvasSize{getCanvasSize(SDLDevice::instance().getWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);
        glUseProgram(getShaderProgram()->getProgramID());
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    auto Color2DRenderer::restoreState() -> void
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glUseProgram(0);
    }

    auto Color2DRenderer::setupAttributeLayout() const -> void
    {
        constexpr int k_stride{7};

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              reinterpret_cast<void *>(sizeof(float) * 0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * k_stride,
                              // NOLINTNEXTLINE(performance-no-int-to-ptr)
                              reinterpret_cast<void *>(sizeof(float) * 3));
        glEnableVertexAttribArray(1);
    }

    auto Color2DRenderer::drawingOperationIsCached(int uniqueRenderID) const -> bool
    {
        return m_operationsCache.contains(uniqueRenderID);
    }
}
