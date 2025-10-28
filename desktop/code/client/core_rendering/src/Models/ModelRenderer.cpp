//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ModelRenderer.hpp"

#include "Base/ShaderProgram.hpp"

#include "Theme0Properties.hpp"

#include "Models/ModelBank.hpp"

#include "Models/Construction/Model.hpp"

#include "SDLDevice.hpp"

#include "Textures/TextureBank.hpp"

namespace Forradia
{
    void ModelRenderer::Initialize()
    {
        String vertexShaderSource{
            this->GetVertexShaderSource()};

        String fragmentShaderSource{
            this->GetFragmentShaderSource()};

        m_shaderProgram = std::make_shared<ShaderProgram>(
            vertexShaderSource, fragmentShaderSource);
    }

    void ModelRenderer::Cleanup()
    {
        for (auto &entry : m_operationsMemory)
        {
            for (auto &entry2 : entry.second)
            {
                for (auto &entry3 : entry2.second)
                {
                    for (auto &entry4 : entry3.second)
                    {
                        glDeleteVertexArrays(
                            1, &entry4.second.vao);

                        glDeleteBuffers(1,
                                        &entry4.second.ibo);

                        glDeleteBuffers(1,
                                        &entry4.second.vbo);
                    }
                }
            }
        }

        glUseProgram(0);
    }

    void ModelRenderer::DrawModel(int modelNameHash,
                                  float x, float y,
                                  float elevation,
                                  Point3F cameraPosition,
                                  float elevationHeight)
    {
        x += _<Theme0::Theme0Properties>().GetTileSize() *
             4.0f / 2.0f;

        y += _<Theme0::Theme0Properties>().GetTileSize() *
             4.0f / 2.0f;

        glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_FRONT);

        auto model{_<ModelBank>().GetModel(modelNameHash)};

        auto &meshes{model->GetMeshesRef()};

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width,
                   canvasSize.height);

        glUseProgram(m_shaderProgram->GetProgramID());

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA,
                            GL_ONE_MINUS_DST_ALPHA, GL_ONE);

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto needCreateBuffers{false};

        if (m_operationsMemory.contains(x) &&
            m_operationsMemory.at(x).contains(y) &&
            m_operationsMemory.at(x).at(y).contains(
                elevation) &&
            m_operationsMemory.at(x)
                .at(y)
                .at(elevation)
                .contains(modelNameHash))
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
            auto &entry = m_operationsMemory.at(x)
                              .at(y)
                              .at(elevation)
                              .at(modelNameHash);

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            if (x != entry.x || y != entry.y ||
                elevation != entry.z)
            {
                needFillBuffers = true;

                entry.x = x;

                entry.y = y;

                entry.z = elevation;
            }
        }
        else
        {
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            ModelRenderingOperation entry;

            entry.vao = vao;

            entry.ibo = ibo;

            entry.vbo = vbo;

            entry.x = x;

            entry.y = y;

            entry.z = elevation;

            m_operationsMemory[x][y][elevation]
                              [modelNameHash] = entry;

            needFillBuffers = true;
        }
        if (needFillBuffers)
        {

            Vector<unsigned int> indicesVector;

            Vector<glm::vec3> normals;

            Vector<float> verticesVector;

            auto i{0};

            for (auto &mesh : meshes)
            {
                for (auto &vertex : mesh.vertices)
                {
                    verticesVector.push_back(
                        x +
                        vertex.position.x * k_modelScale);

                    verticesVector.push_back(
                        y +
                        vertex.position.y * k_modelScale);

                    verticesVector.push_back(
                        elevation * elevationHeight +
                        vertex.position.z * k_modelScale);

                    verticesVector.push_back(
                        vertex.normal.x);

                    verticesVector.push_back(
                        vertex.normal.y);

                    verticesVector.push_back(
                        vertex.normal.z);

                    verticesVector.push_back(vertex.uv.x);

                    verticesVector.push_back(vertex.uv.y);
                }

                for (auto &index : mesh.indices)
                {
                    indicesVector.push_back(
                        i + mesh.indices[index]);
                }

                i += mesh.vertices.size();
            }

            auto verticesCount{verticesVector.size() / 8};

            auto indicesCount{indicesVector.size()};

            auto vertices{verticesVector.data()};

            auto indices{indicesVector.data()};

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(indices[0]) * indicesCount,
                         indices, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(vertices[0]) * 8 *
                             verticesCount,
                         vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(vertices[0]) * 8,
                                  0);

            glEnableVertexAttribArray(0);

            glVertexAttribPointer(
                1, 3, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 8,
                (void *)(sizeof(vertices[0]) * 3));

            glEnableVertexAttribArray(1);

            glVertexAttribPointer(
                2, 2, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 8,
                (void *)(sizeof(vertices[0]) * 6));

            glEnableVertexAttribArray(2);

            auto &entry = m_operationsMemory.at(x)
                              .at(y)
                              .at(elevation)
                              .at(modelNameHash);

            entry.verticesCount = verticesCount;
        }

        auto &entry =
            m_operationsMemory.at(x).at(y).at(elevation).at(
                modelNameHash);

        glm::mat4 modelMatrix = glm::mat4(1.0f);

        // lookAt function takes camera position, camera
        // target and up vector.

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

        GLuint matrixProjection = glGetUniformLocation(
            m_shaderProgram->GetProgramID(), "projection");
        glUniformMatrix4fv(matrixProjection, 1, GL_FALSE,
                           &projectionMatrix[0][0]);

        GLuint matrixModel = glGetUniformLocation(
            m_shaderProgram->GetProgramID(), "model");
        glUniformMatrix4fv(matrixModel, 1, GL_FALSE,
                           &modelMatrix[0][0]);

        GLuint matrixView = glGetUniformLocation(
            m_shaderProgram->GetProgramID(), "view");

        glUniformMatrix4fv(matrixView, 1, GL_FALSE,
                           &cameraMatrix[0][0]);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        auto textureName{meshes.at(0).textures.at(0).path};

        auto textureNameHash{Hash(textureName)};

        auto textureID{
            _<TextureBank>().GetTexture(textureNameHash)};

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLES, entry.verticesCount,
                       GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisable(GL_DEPTH_TEST);
    }
}