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
        for (auto &entry : m_operationsMemory)
        {
            for (auto &entry2 : entry.second)
            {
                for (auto &entry3 : entry2.second)
                {
                    glDeleteVertexArrays(
                        1, &entry3.second.vao);

                    glDeleteBuffers(1, &entry3.second.ibo);

                    glDeleteBuffers(1, &entry3.second.vbo);
                }
            }
        }

        glUseProgram(0);
    }

    void GroundRenderer::DrawTile(
        int imageNameHash, int xCoordinate, int yCoordinate,
        float tileSize, Point3F cameraPosition,
        Vector<float> &elevations, float elevationHeight)
    {
        auto textureID{
            _<TextureBank>().GetTexture(imageNameHash)};

        auto x{tileSize * (xCoordinate)};

        auto y{tileSize * (yCoordinate)};

        auto width{tileSize};

        auto height{tileSize};

        Vector<float> vertices{
            {x,
             y,
             elevations.at(0) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             0.0,
             0.0,
             x + width,
             y,
             elevations.at(1) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             0.0,
             x + width + width,
             y,
             elevations.at(2) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x,
             y + height,
             elevations.at(3) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             0.0,
             1.0,
             x + width,
             y + height,
             elevations.at(4) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x + width + width,
             y + height,
             elevations.at(5) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x,
             y + height + height,
             elevations.at(6) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x + width,
             y + height + height,
             elevations.at(7) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x + width + width,
             y + height + height,
             elevations.at(8) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0}};

        GroundRenderer::DrawTexture(textureID, vertices,
                                    cameraPosition);
    }

    void
    GroundRenderer::DrawTexture(GLuint textureID,
                                Vector<float> &verticesVec,
                                Point3F cameraPosition)
    {
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

        auto verticesNoNormals = verticesVec.data();

        unsigned int indices[] = {0, 1, 2, 3};

        Vector<glm::vec3> normals;

        auto verticesCount{4};

        auto indicesCount{4};

        auto _00x{verticesNoNormals[0 * 8 + 0]};
        auto _00y{verticesNoNormals[0 * 8 + 1]};
        auto _00z{verticesNoNormals[0 * 8 + 2]};
        auto _10x{verticesNoNormals[1 * 8 + 0]};
        auto _10y{verticesNoNormals[1 * 8 + 1]};
        auto _10z{verticesNoNormals[1 * 8 + 2]};
        auto _20x{verticesNoNormals[2 * 8 + 0]};
        auto _20y{verticesNoNormals[2 * 8 + 1]};
        auto _20z{verticesNoNormals[2 * 8 + 2]};
        auto _01x{verticesNoNormals[3 * 8 + 0]};
        auto _01y{verticesNoNormals[3 * 8 + 1]};
        auto _01z{verticesNoNormals[3 * 8 + 2]};
        auto _11x{verticesNoNormals[4 * 8 + 0]};
        auto _11y{verticesNoNormals[4 * 8 + 1]};
        auto _11z{verticesNoNormals[4 * 8 + 2]};
        auto _21x{verticesNoNormals[5 * 8 + 0]};
        auto _21y{verticesNoNormals[5 * 8 + 1]};
        auto _21z{verticesNoNormals[5 * 8 + 2]};
        auto _02x{verticesNoNormals[6 * 8 + 0]};
        auto _02y{verticesNoNormals[6 * 8 + 1]};
        auto _02z{verticesNoNormals[6 * 8 + 2]};
        auto _12x{verticesNoNormals[7 * 8 + 0]};
        auto _12y{verticesNoNormals[7 * 8 + 1]};
        auto _12z{verticesNoNormals[7 * 8 + 2]};
        auto _22x{verticesNoNormals[8 * 8 + 0]};
        auto _22y{verticesNoNormals[8 * 8 + 1]};
        auto _22z{verticesNoNormals[8 * 8 + 2]};

        glm::vec3 v00 = {_00x, _00y, _00z};
        glm::vec3 v10 = {_10x, _10y, _10z};
        glm::vec3 v20 = {_20x, _20y, _20z};
        glm::vec3 v01 = {_01x, _01y, _01z};
        glm::vec3 v11 = {_11x, _11y, _11z};
        glm::vec3 v21 = {_21x, _21y, _21z};
        glm::vec3 v02 = {_02x, _02y, _02z};
        glm::vec3 v12 = {_12x, _12y, _12z};
        glm::vec3 v22 = {_22x, _22y, _22z};

        glm::vec3 normal00 =
            this->ComputeNormal(v10, v00, v01);
        glm::vec3 normal10 =
            this->ComputeNormal(v20, v10, v11);
        glm::vec3 normal11 =
            this->ComputeNormal(v21, v11, v12);
        glm::vec3 normal01 =
            this->ComputeNormal(v11, v01, v02);

        normal00.z *= -1.0f;
        normal10.z *= -1.0f;
        normal11.z *= -1.0f;
        normal01.z *= -1.0f;

        normals.push_back(normal00);
        normals.push_back(normal10);
        normals.push_back(normal11);
        normals.push_back(normal01);

        Vector<float> verticesVector;

        auto fn{
            [&](int i, int j)
            {
                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 0]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 1]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 2]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 3]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 4]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 5]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 6]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 7]);

                verticesVector.push_back(normals.at(j).x);

                verticesVector.push_back(normals.at(j).y);

                verticesVector.push_back(normals.at(j).z);
            }};

        fn(0, 0);

        fn(1, 1);

        fn(4, 2);

        fn(3, 3);

        auto vertices{verticesVector.data()};

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto needCreateBuffers{false};

        if (m_operationsMemory.contains(
                verticesVec.at(0)) &&
            m_operationsMemory.at(verticesVec.at(0))
                .contains(verticesVec.at(1)) &&
            m_operationsMemory.at(verticesVec.at(0))
                .at(verticesVec.at(1))
                .contains(textureID))
        {
            needCreateBuffers = false;
        }
        else
        {
            needCreateBuffers = true;

            glGenVertexArrays(1, &vao);

            glGenBuffers(1, &vbo);

            glGenBuffers(1, &ibo);
        }

        auto needFillBuffers{false};

        if (!needCreateBuffers)
        {
            auto &entry =
                m_operationsMemory.at(verticesVec.at(0))
                    .at(verticesVec.at(1))
                    .at(textureID);

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            if (verticesVec.at(0) != entry.x ||
                verticesVec.at(1) != entry.y)
            {
                needFillBuffers = true;

                entry.x = verticesVec.at(0);

                entry.y = verticesVec.at(1);
            }
        }
        else
        {
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            GroundRenderingOperation entry;

            entry.vao = vao;

            entry.ibo = ibo;

            entry.vbo = vbo;

            entry.x = verticesVec.at(0);

            entry.y = verticesVec.at(1);

            m_operationsMemory[verticesVec.at(
                0)][verticesVec.at(1)][textureID] = entry;

            needFillBuffers = true;
        }
        if (needFillBuffers)
        {
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

        // perspective function takes field of view, aspect
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

    glm::vec3 GroundRenderer::ComputeNormal(glm::vec3 p1,
                                            glm::vec3 p2,
                                            glm::vec3 p3)
    {
        // Uses p2 as a new origin for p1, p3.

        auto a = p3 - p2;

        auto b = p1 - p2;

        // Compute the cross product a X b to get the face
        // normal.

        return glm::normalize(glm::cross(a, b));
    }
}