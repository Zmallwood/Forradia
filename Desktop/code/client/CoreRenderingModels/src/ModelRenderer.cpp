//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "ModelRenderer.hpp"
#include "SDLDevice.hpp"
#include "ShaderProgram.hpp"

namespace Forradia {
    void ModelRenderer::Cleanup() {
        // For each entry in the operations cache.
        for (auto &entry : m_operationsCache) {
            // Delete the buffer objects and vertex array objects.

            glDeleteBuffers(1, &entry.second.ibo);
            glDeleteBuffers(1, &entry.second.vbo);
            glDeleteVertexArrays(1, &entry.second.vao);
        }
        // Clear the operations cache.
        m_operationsCache.clear();
    }

    void ModelRenderer::SetupState() const {
        // Enable depth testing.
        glEnable(GL_DEPTH_TEST);

        // Get the canvas size and set the viewport.

        auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width, canvasSize.height);

        // Use the shader program.
        glUseProgram(GetShaderProgram()->GetProgramID());

        // Enable blending.

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
    }

    void ModelRenderer::RestoreState() const {
        // Unbind the vertex array object, vertex buffer object and index buffer object.

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // Disable depth testing.
        glDisable(GL_DEPTH_TEST);
    }

    void ModelRenderer::SetupAttributeLayout() const {
        // Setup the attribute layout.

        // Position.

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                              (void *)(sizeof(float) * 0));

        glEnableVertexAttribArray(0);

        // Normal.

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                              (void *)(sizeof(float) * 3));

        glEnableVertexAttribArray(1);

        // Texture coordinates (UV coordinates).

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                              (void *)(sizeof(float) * 6));

        glEnableVertexAttribArray(2);
    }

    bool ModelRenderer::DrawingOperationIsCached(int modelNameHash) const {
        // Check if the drawing operation is cached.
        //
        // Note: For this renderer the modelNameHash can be used as a key since what changes
        // between different rendering operations is the model matrix, not the vertex data
        // (which is the case for the other renderers).
        return m_operationsCache.contains(modelNameHash);
    }

    void ModelRenderer::InitializeDerived() {
        // Obtain the layout location for the uniform matrices.

        // Projection matrix.
        m_layoutLocationProjectionMatrix =
            glGetUniformLocation(GetShaderProgram()->GetProgramID(), "projection");

        // View matrix.
        m_layoutLocationViewMatrix =
            glGetUniformLocation(GetShaderProgram()->GetProgramID(), "view");

        // Model matrix.
        m_layoutLocationModelMatrix =
            glGetUniformLocation(GetShaderProgram()->GetProgramID(), "model");
    }
}