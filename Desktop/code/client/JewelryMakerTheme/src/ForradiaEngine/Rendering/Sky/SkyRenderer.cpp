/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "SkyRenderer.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Devices/SDLDevice.hpp"
#include "ForradiaEngine/Rendering/Base/ShaderProgram.hpp"

namespace ForradiaEngine
{
    auto SkyRenderer::cleanup() -> void
    {
        if (m_vao != 0)
        {
            glDeleteVertexArrays(1, &m_vao);
        }

        if (m_ibo != 0)
        {
            glDeleteBuffers(1, &m_ibo);
        }

        if (m_vbo != 0)
        {
            glDeleteBuffers(1, &m_vbo);
        }

        m_vao = 0;
        m_ibo = 0;
        m_vbo = 0;

        m_indexCount = 0;

        m_initialized = false;
    }

    auto SkyRenderer::setupState() const -> void
    {
        auto canvasSize{getCanvasSize(SDLDevice::instance().getWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);
        glUseProgram(getShaderProgram()->getProgramID());

        // Enable depth testing with LEQUAL.
        // The sky vertices are set to far plane (z = w) in the vertex shader,
        // so they will render behind other geometry but fill empty space.
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Disable depth writing so the sky doesn't occlude other objects.
        glDepthMask(GL_FALSE);

        // Disable face culling entirely to ensure all triangles render.
        // Since we're viewing from inside the dome, we need to see all faces.
        glDisable(GL_CULL_FACE);
    }

    auto SkyRenderer::restoreState() -> void
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDepthMask(GL_TRUE);

        glDisable(GL_DEPTH_TEST);
    }

    auto SkyRenderer::setupAttributeLayout() const -> void
    {
        // Position (3 floats).
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3,
                              static_cast<void *>(nullptr));
        glEnableVertexAttribArray(0);
    }

    auto SkyRenderer::initializeDerived() -> void
    {
        m_layoutLocationMVP = glGetUniformLocation(getShaderProgram()->getProgramID(), "MVP");
        m_layoutLocationSunDirection =
            glGetUniformLocation(getShaderProgram()->getProgramID(), "sunDirection");
        m_layoutLocationSunElevation =
            glGetUniformLocation(getShaderProgram()->getProgramID(), "sunElevation");

        // Check if uniform locations are valid (should not be -1).
        if (m_layoutLocationMVP == -1 || m_layoutLocationSunDirection == -1 ||
            m_layoutLocationSunElevation == -1)
        {
            throwError("Uniform locations not found - shader might have compilation errors.");
        }
    }
}
