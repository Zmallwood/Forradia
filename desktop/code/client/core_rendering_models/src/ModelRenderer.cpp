//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ModelRenderer.hpp"

#include "ShaderProgram.hpp"

#include "SDLDevice.hpp"

namespace Forradia
{
    void ModelRenderer::Cleanup()
    {
        for (auto &entry : m_operationsCache)
        {
            glDeleteVertexArrays(1, &entry.second.vao);

            glDeleteBuffers(1, &entry.second.ibo);

            glDeleteBuffers(1, &entry.second.vbo);
        }
    }

    void ModelRenderer::SetupState() const
    {
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_FRONT);

        glFrontFace(GL_CCW);

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width,
                   canvasSize.height);

        glUseProgram(GetShaderProgram()->GetProgramID());

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA,
                            GL_ONE_MINUS_DST_ALPHA, GL_ONE);
    }

    void ModelRenderer::RestoreState() const
    {
        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisable(GL_DEPTH_TEST);
    }

    void ModelRenderer::SetupAttributeLayout() const
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 8,
                              (void *)(sizeof(float) * 0));

        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 8,
                              (void *)(sizeof(float) * 3));

        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 8,
                              (void *)(sizeof(float) * 6));

        glEnableVertexAttribArray(2);
    }
}