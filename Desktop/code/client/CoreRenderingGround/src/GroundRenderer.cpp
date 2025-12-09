//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "GroundRenderer.hpp"
#include "SDLDevice.hpp"
#include "ShaderProgram.hpp"

namespace Forradia
{
    void GroundRenderer::Cleanup()
    {
        // Go through the operations cache.
        for (auto &entry : m_operationsCache)
        {
            // Delete the vertex array objects and buffer objects in the operations cache.

            glDeleteBuffers(1, &entry.second.ibo);
            glDeleteBuffers(1, &entry.second.vbo);
            glDeleteVertexArrays(1, &entry.second.vao);
        }

        // Clear the operations cache.
        m_operationsCache.clear();
    }

    void GroundRenderer::SetupState() const
    {
        // Set up the state for the renderer.

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        // Get the canvas size and set the viewport.

        auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);

        // Use the shader program.
        glUseProgram(GetShaderProgram()->GetProgramID());

        // Enable blending.

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void GroundRenderer::RestoreState() const
    {
        // Unbind the vertex array object, vertex buffer object and index buffer object.

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Disable depth testing, culling, blending.

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
    }

    void GroundRenderer::Reset()
    {
        // Clean up the renderer.
        this->Cleanup();
    }

    void GroundRenderer::SetupAttributeLayout() const
    {
        // Set up the attribute layout for the vertex shader.

        // Position.

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11,
                              (void *)(sizeof(float) * 0));

        glEnableVertexAttribArray(0);

        // Color.

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11,
                              (void *)(sizeof(float) * 3));

        glEnableVertexAttribArray(1);

        // Texture coordinates.

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11,
                              (void *)(sizeof(float) * 6));

        glEnableVertexAttribArray(2);

        // Normals.

        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11,
                              (void *)(sizeof(float) * 8));

        glEnableVertexAttribArray(3);
    }

    bool GroundRenderer::DrawingOperationIsCached(int uniqueRenderID) const
    {
        // Check if the unique render ID is in the operations cache.
        return m_operationsCache.contains(uniqueRenderID);
    }

    void GroundRenderer::InitializeDerived()
    {
        // Get the layout location for the uniform MVP matrix.
        m_layoutLocationMVP = glGetUniformLocation(GetShaderProgram()->GetProgramID(), "MVP");
    }
}