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
        for (auto &entryLevel1 : m_operationsCache)
        {
            for (auto &entryLevel2 : entryLevel1.second)
            {
                for (auto &entryLevel3 : entryLevel2.second)
                {
                    for (auto &entryLevel4 :
                         entryLevel3.second)
                    {
                        glDeleteVertexArrays(
                            1, &entryLevel4.second.vao);

                        glDeleteBuffers(
                            1, &entryLevel4.second.ibo);

                        glDeleteBuffers(
                            1, &entryLevel4.second.vbo);
                    }
                }
            }
        }

        glUseProgram(0);
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

    void ModelRenderer::ResetState() const
    {
        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisable(GL_DEPTH_TEST);
    }
}