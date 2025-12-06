//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "SkyRenderer.hpp"
#include "GUIChatBox.hpp"
#include "ShaderProgram.hpp"

namespace Forradia
{
    void SkyRenderer::Cleanup()
    {
        // Delete the vertex array object, index buffer object and vertex buffer object.

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

        // Reset the object variables.

        m_vao = 0;

        m_ibo = 0;

        m_vbo = 0;

        // Reset the index count and initialized flag.

        m_indexCount = 0;

        m_initialized = false;
    }

    void SkyRenderer::SetupState() const
    {
        // Get the canvas size and set the viewport.

        auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);

        // Use the shader program.

        glUseProgram(GetShaderProgram()->GetProgramID());

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

    void SkyRenderer::RestoreState() const
    {
        // Unbind the vertex array object, vertex buffer object and index buffer object.

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Restore depth writing.

        glDepthMask(GL_TRUE);

        // Disable depth testing.

        glDisable(GL_DEPTH_TEST);
    }

    void SkyRenderer::SetupAttributeLayout() const
    {
        // Set up the attribute layout for the vertex shader.
        // Position (3 floats).

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);

        glEnableVertexAttribArray(0);
    }

    void SkyRenderer::InitializeDerived()
    {
        // Get the layout locations for the uniforms.

        m_layoutLocationMVP = glGetUniformLocation(GetShaderProgram()->GetProgramID(), "MVP");

        m_layoutLocationSunDirection =
            glGetUniformLocation(GetShaderProgram()->GetProgramID(), "sunDirection");

        m_layoutLocationSunElevation =
            glGetUniformLocation(GetShaderProgram()->GetProgramID(), "sunElevation");

        // Check if uniform locations are valid (should not be -1).

        if (m_layoutLocationMVP == -1 || m_layoutLocationSunDirection == -1 ||
            m_layoutLocationSunElevation == -1)
        {
            // Let the player know that the shader might have compilation errors.

            _<GUIChatBox>().Print(
                "Uniform locations not found - shader might have compilation errors.");
        }
    }
}