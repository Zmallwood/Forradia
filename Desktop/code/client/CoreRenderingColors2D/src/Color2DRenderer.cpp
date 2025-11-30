//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Color2DRenderer.hpp"

#include "SDLDevice.hpp"

#include "ShaderProgram.hpp"

namespace AAK
{
    namespace Forradia
    {
        void Color2DRenderer::Cleanup()
        {
            // Delete the vertex array objects, index buffer objects and vertex buffer objects.

            for (auto &entry : m_operationsCache)
            {
                glDeleteBuffers(1, &entry.second.ibo);

                glDeleteBuffers(1, &entry.second.vbo);

                glDeleteVertexArrays(1, &entry.second.vao);
            }

            // Clear the operations cache.

            m_operationsCache.clear();
        }

        void Color2DRenderer::SetupState() const
        {
            // Get the canvas size in pixels.

            auto canvasSize{GetCanvasSize(_<SDLDevice>().GetWindow())};

            // Set the viewport to the canvas size.

            glViewport(0, 0, canvasSize.width, canvasSize.height);

            // Use the shader program.

            glUseProgram(GetShaderProgram()->GetProgramID());

            // Enable blending and set the blend function.

            glEnable(GL_BLEND);

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        void Color2DRenderer::RestoreState() const
        {
            // Unbind the vertex array object, index buffer object and vertex buffer object from the
            // current shader program.

            glBindVertexArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            // Unuse the shader program.

            glUseProgram(0);
        }

        void Color2DRenderer::SetupAttributeLayout() const
        {
            // Setup the attribute layout for the position.

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7,
                                  (void *)(sizeof(float) * 0));

            glEnableVertexAttribArray(0);

            // Setup the attribute layout for the color.

            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7,
                                  (void *)(sizeof(float) * 3));

            glEnableVertexAttribArray(1);
        }

        bool Color2DRenderer::DrawingOperationIsCached(int uniqueRenderID) const
        {
            // Check if the drawing operation is cached.

            return m_operationsCache.contains(uniqueRenderID);
        }
    }
}