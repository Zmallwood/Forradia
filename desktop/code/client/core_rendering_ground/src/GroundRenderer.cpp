//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GroundRenderer.hpp"

#include "ShaderProgram.hpp"

#include "SDLDevice.hpp"

namespace Forradia
{
    void GroundRenderer::Cleanup()
    {
        for (auto &entryLevel1 : m_operationsCache)
        {
            for (auto &entryLevel2 : entryLevel1.second)
            {
                for (auto &entryLevel3 : entryLevel2.second)
                {
                    glDeleteVertexArrays(
                        1, &entryLevel3.second.vao);

                    glDeleteBuffers(
                        1, &entryLevel3.second.ibo);

                    glDeleteBuffers(
                        1, &entryLevel3.second.vbo);
                }
            }
        }
    }
    void GroundRenderer::SetupState() const
    {
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_BACK);

        glFrontFace(GL_CW);

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width,
                   canvasSize.height);

        glUseProgram(GetShaderProgram()->GetProgramID());

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void GroundRenderer::RestoreState() const
    {
        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisable(GL_DEPTH_TEST);

        glDisable(GL_CULL_FACE);

        glDisable(GL_BLEND);
    }

    void GroundRenderer::SetupAttributeLayout() const
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 11,
                              (void *)(sizeof(float) * 0));

        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 11,
                              (void *)(sizeof(float) * 3));

        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 11,
                              (void *)(sizeof(float) * 6));

        glEnableVertexAttribArray(2);

        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
                              sizeof(float) * 11,
                              (void *)(sizeof(float) * 8));

        glEnableVertexAttribArray(3);
    }
}