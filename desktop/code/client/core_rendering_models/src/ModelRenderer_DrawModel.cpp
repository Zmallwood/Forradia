//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "ModelRenderer.hpp"

#include "Textures/TextureBank.hpp"

#include "Models/ModelBank.hpp"

#include "SDLDevice.hpp"

#include "Theme0Properties.hpp"

#include "Models/Construction/Model.hpp"

#include "ShaderProgram.hpp"

#include "3D/Camera.hpp"

#include "TimeUtilities.hpp"

namespace Forradia
{
    void ModelRenderer::DrawModel(int modelNameHash,
                                  float x, float y,
                                  float elevation,
                                  float elevationHeight)
    {
        // Setup state.

        this->SetupState();

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto needFillBuffers{false};

        if (this->DrawingOperationIsCached(modelNameHash))
        {
            auto &entry{
                m_operationsCache.at(modelNameHash)};

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

            ModelRenderingOperation entry;

            entry.vao = vao;

            entry.ibo = ibo;

            entry.vbo = vbo;

            m_operationsCache[modelNameHash] = entry;

            needFillBuffers = true;
        }

        auto model{_<ModelBank>().GetModel(modelNameHash)};

        auto &meshes{model->GetMeshesRef()};

        if (needFillBuffers)
        {
            // std::cout << GetTicks() << std::endl;
            Vector<unsigned short> indicesVector;

            Vector<float> verticesVector;

            auto i{0};

            for (auto &mesh : meshes)
            {
                for (auto &vertex : mesh.vertices)
                {
                    verticesVector.push_back(
                        vertex.position.x * k_modelScale);

                    verticesVector.push_back(
                        vertex.position.y * k_modelScale);

                    verticesVector.push_back(
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

            this->SetupAttributeLayout();

            auto &entry{
                m_operationsCache.at(modelNameHash)};

            entry.verticesCount = verticesCount;
        }

        auto &entry{m_operationsCache.at(modelNameHash)};

        auto modelMatrix{glm::mat4(1.0f)};

        modelMatrix = glm::translate(
            modelMatrix,
            glm::vec3(x, y, elevation * elevationHeight));

        auto viewMatrix{_<Camera>().GetViewMatrix()};

        auto projectionMatrix{
            _<Camera>().GetProjectionMatrix()};

        auto matrixProjection{glGetUniformLocation(
            GetShaderProgram()->GetProgramID(),
            "projection")};

        glUniformMatrix4fv(matrixProjection, 1, GL_FALSE,
                           &projectionMatrix[0][0]);

        auto matrixModel{glGetUniformLocation(
            GetShaderProgram()->GetProgramID(), "model")};

        glUniformMatrix4fv(matrixModel, 1, GL_FALSE,
                           &modelMatrix[0][0]);

        auto matrixView{glGetUniformLocation(
            GetShaderProgram()->GetProgramID(), "view")};

        glUniformMatrix4fv(matrixView, 1, GL_FALSE,
                           &viewMatrix[0][0]);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        auto textureName{meshes.at(0).textures.at(0).path};

        auto textureNameHash{Hash(textureName)};

        auto textureID{
            _<TextureBank>().GetTexture(textureNameHash)};

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLES, entry.verticesCount,
                       GL_UNSIGNED_SHORT, nullptr);

        this->RestoreState();
    }
}