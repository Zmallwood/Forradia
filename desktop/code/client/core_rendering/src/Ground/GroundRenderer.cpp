//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GroundRenderer.hpp"

#include "ShaderProgram.hpp"

#include "Textures/TextureBank.hpp"

#include "SDLDevice.hpp"

namespace Forradia
{
    void GroundRenderer::Cleanup()
    {
        for (auto &entryLevel1 : m_operationsMemory)
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

        glUseProgram(0);
    }

    void GroundRenderer::DrawTile(
        int imageNameHash, int xCoordinate, int yCoordinate,
        float tileSize, Point3F cameraPosition,
        const Vector<float> &elevations,
        float elevationHeight)
    {
        auto textureID{
            _<TextureBank>().GetTexture(imageNameHash)};

        glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_FRONT);

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width,
                   canvasSize.height);

        glUseProgram(GetShaderProgram()->GetProgramID());

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        if (m_operationsMemory.contains(xCoordinate) &&
            m_operationsMemory.at(xCoordinate)
                .contains(yCoordinate) &&
            m_operationsMemory.at(xCoordinate)
                .at(yCoordinate)
                .contains(textureID))
        {
            auto &entry = m_operationsMemory.at(xCoordinate)
                              .at(yCoordinate)
                              .at(textureID);

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        }
        else
        {
            glGenVertexArrays(1, &vao);

            glGenBuffers(1, &vbo);

            glGenBuffers(1, &ibo);

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            GroundRenderingOperation entry;

            entry.vao = vao;

            entry.ibo = ibo;

            entry.vbo = vbo;

            m_operationsMemory[xCoordinate][yCoordinate]
                              [textureID] = entry;

            auto verticesNoNormals{
                this->CalcTileVerticesNoNormals(
                    xCoordinate, yCoordinate, tileSize,
                    elevations, elevationHeight)};

            unsigned int indices[] = {0, 1, 2, 3};

            auto verticesCount{4};

            auto indicesCount{4};

            auto verticesVector{
                this->CalcTileVerticesWithNormals(
                    verticesNoNormals)};

            auto vertices{verticesVector.data()};

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(indices[0]) * indicesCount,
                         indices, GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(vertices[0]) * 11 *
                             verticesCount,
                         vertices, GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(vertices[0]) * 11,
                                  0);

            glEnableVertexAttribArray(0);

            glVertexAttribPointer(
                1, 3, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 11,
                (void *)(sizeof(vertices[0]) * 3));

            glEnableVertexAttribArray(1);

            glVertexAttribPointer(
                2, 2, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 11,
                (void *)(sizeof(vertices[0]) * 6));

            glEnableVertexAttribArray(2);

            glVertexAttribPointer(
                3, 3, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 11,
                (void *)(sizeof(vertices[0]) * 8));

            glEnableVertexAttribArray(3);
        }

        glm::mat4 modelMatrix = glm::mat4(1.0f);

        glm::mat4 cameraMatrix = glm::lookAt(
            glm::vec3(cameraPosition.x,
                      cameraPosition.y - 2.0f,
                      -cameraPosition.z + 2.5f),
            glm::vec3(cameraPosition.x, cameraPosition.y,
                      -cameraPosition.z),
            glm::vec3(0.0f, 0.0f, -1.0f));

        auto aspectRatio{
            CalcAspectRatio(_<SDLDevice>().GetWindow())};

        // Perspective function takes field of view, aspect
        // ratio, near clipping distance and far clipping
        // distance.

        glm::mat4 projectionMatrix = glm::perspective(
            90.0f, aspectRatio, 0.1f, 100.0f);

        glm::mat4 finalMatrix =
            projectionMatrix * cameraMatrix * modelMatrix;

        GLuint mvpMatrixID = glGetUniformLocation(
            GetShaderProgram()->GetProgramID(), "MVP");

        glUniformMatrix4fv(mvpMatrixID, 1, GL_FALSE,
                           &finalMatrix[0][0]);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT,
                       nullptr);

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisable(GL_DEPTH_TEST);
    }
}