/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Models/Construction/Model.hpp"
#include "3D/Camera.hpp"
#include "CreatureIndex.hpp"
#include "ModelRenderer.hpp"
#include "Models/ModelBank.hpp"
#include "ObjectIndex.hpp"
#include "Textures/TextureBank.hpp"
#include "Theme0Properties.hpp"

namespace Forradia {
    auto ModelRenderer::DrawModel(int modelNameHash, float x, float y, float elevation,
                                  float modelScaling) -> void {
        this->SetupState();

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto model{_<ModelBank>().GetModel(modelNameHash)};
        auto &meshes{model->GetMeshesRef()};

        // If the drawing operation is cached.
        if (this->DrawingOperationIsCached(modelNameHash)) {
            auto &entry{m_operationsCache.at(modelNameHash)};

            vao = entry.vao;
            ibo = entry.ibo;
            vbo = entry.vbo;

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        } else {
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

            std::vector<unsigned short> indicesVector;
            std::vector<float> verticesVector;

            // To contain the index of the first vertex of the next mesh.
            auto indexFirstVertexOfMesh{0};

            float totalModelScaling{k_globalModelScaling};

            if (!_<Theme0::ObjectIndex>().GetIgnoreIndividualModelScaling(modelNameHash))
                totalModelScaling *= modelScaling;

            if (_<Theme0::ObjectIndex>().ObjectEntryExists(modelNameHash))
                totalModelScaling *= _<Theme0::ObjectIndex>().GetModelScaling(modelNameHash);

            if (_<Theme0::CreatureIndex>().CreatureEntryExists(modelNameHash))
                totalModelScaling *= _<Theme0::CreatureIndex>().GetModelScaling(modelNameHash);

            // For each mesh.
            for (auto &mesh : meshes) {
                // For each vertex.
                for (auto &vertex : mesh.vertices) {
                    // Add position.
                    verticesVector.push_back(vertex.position.x * totalModelScaling);
                    verticesVector.push_back(vertex.position.y * totalModelScaling);
                    verticesVector.push_back(vertex.position.z * totalModelScaling);

                    // Add normal.
                    verticesVector.push_back(vertex.normal.x);
                    verticesVector.push_back(vertex.normal.y);
                    verticesVector.push_back(vertex.normal.z);

                    // Add texture coordinates.
                    verticesVector.push_back(vertex.uv.x);
                    verticesVector.push_back(vertex.uv.y);
                }

                // For each index of the mesh.
                for (auto &index : mesh.indices) {
                    // Calculate the total index.
                    auto totalIndex{indexFirstVertexOfMesh + mesh.indices[index]};

                    // Add the total index to the indices vector.
                    indicesVector.push_back(totalIndex);
                }

                // Update the index of the first vertex of the next mesh.
                indexFirstVertexOfMesh += mesh.vertices.size();
            }

            constexpr auto k_floatsPerVertex{8};

            auto verticesCount{verticesVector.size() / k_floatsPerVertex};
            auto indicesCount{indicesVector.size()};

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesVector.data()[0]) * indicesCount,
                         indicesVector.data(), GL_STATIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, sizeof(verticesVector.data()[0]) * 8 * verticesCount,
                         verticesVector.data(), GL_STATIC_DRAW);

            this->SetupAttributeLayout();

            entry.verticesCount = verticesCount;

            m_operationsCache[modelNameHash] = entry;
        }

        auto elevationHeight{_<Theme0::Theme0Properties>().GetElevationHeight()};

        auto levitationHeight{_<Theme0::CreatureIndex>().GetLevitationHeight(modelNameHash)};

        // Calculate the model matrix. This matrix differs between different rendering
        // operations, even though they use the same model.
        auto modelMatrix{glm::mat4(1.0F)};

        // Translate the model to the position.
        modelMatrix = glm::translate(
            modelMatrix, glm::vec3(x, y, elevation * elevationHeight + levitationHeight));

        if (!_<Theme0::ObjectIndex>().GetIgnoreIndividualModelScaling(modelNameHash))
            modelMatrix = glm::scale(modelMatrix, glm::vec3(modelScaling));

        auto viewMatrix{_<Camera>().GetViewMatrix()};
        auto projectionMatrix{_<Camera>().GetProjectionMatrix()};

        glUniformMatrix4fv(m_layoutLocationProjectionMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
        glUniformMatrix4fv(m_layoutLocationModelMatrix, 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(m_layoutLocationViewMatrix, 1, GL_FALSE, &viewMatrix[0][0]);

        auto textureName{meshes.at(0).textures.at(0).path};
        auto textureNameHash{Hash(textureName)};

        auto textureID{_<TextureBank>().GetTexture(textureNameHash)};
        glBindTexture(GL_TEXTURE_2D, textureID);

        auto &entry{m_operationsCache.at(modelNameHash)};

        glDrawElements(GL_TRIANGLES, entry.verticesCount, GL_UNSIGNED_SHORT, nullptr);

        this->RestoreState();
    }
}
