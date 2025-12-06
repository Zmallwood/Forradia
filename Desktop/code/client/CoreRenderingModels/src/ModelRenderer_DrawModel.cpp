//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Models/Construction/Model.hpp"
#include "3D/Camera.hpp"
#include "CreatureIndex.hpp"
#include "ModelRenderer.hpp"
#include "Models/ModelBank.hpp"
#include "ObjectIndex.hpp"
#include "Textures/TextureBank.hpp"
#include "Theme0Properties.hpp"

namespace Forradia
{
    void ModelRenderer::DrawModel(int modelNameHash, float x, float y, float elevation,
                                  float modelScaling)
    {
        // Setup state.

        this->SetupState();

        // To contain the vertex array object, index buffer object and vertex buffer object.

        GLuint vao;

        GLuint ibo;

        GLuint vbo;

        // Get the model and its meshes from the model bank.

        auto model{_<ModelBank>().GetModel(modelNameHash)};

        auto &meshes{model->GetMeshesRef()};

        // If the drawing operation is cached.

        if (this->DrawingOperationIsCached(modelNameHash))
        {
            // Get the cached drawing operation.

            auto &entry{m_operationsCache.at(modelNameHash)};

            // Get the vertex array object, index buffer object and vertex buffer object.

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            // Bind them as well.

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        }
        else
        {
            // Generate the vertex array object, index buffer object and vertex buffer object.

            glGenVertexArrays(1, &vao);

            glGenBuffers(1, &vbo);

            glGenBuffers(1, &ibo);

            // Bind them as well.

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            // Create a new drawing operation to be cached.

            ModelRenderingOperation entry;

            entry.vao = vao;

            entry.ibo = ibo;

            entry.vbo = vbo;

            // To contain the indices.

            Vector<unsigned short> indicesVector;

            // To contain the vertices.

            Vector<float> verticesVector;

            // To contain the index of the first vertex of the next mesh.

            auto indexFirstVertexOfMesh{0};

            // To contain the total model scaling.

            float totalModelScaling{k_globalModelScaling * modelScaling};

            if (_<Theme0::ObjectIndex>().ObjectEntryExists(modelNameHash))
            {
                totalModelScaling *= _<Theme0::ObjectIndex>().GetModelScaling(modelNameHash);
            }

            if (_<Theme0::CreatureIndex>().CreatureEntryExists(modelNameHash))
            {
                totalModelScaling *= _<Theme0::CreatureIndex>().GetModelScaling(modelNameHash);
            }

            // For each mesh.

            for (auto &mesh : meshes)
            {
                // For each vertex.

                for (auto &vertex : mesh.vertices)
                {
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

                for (auto &index : mesh.indices)
                {
                    // Calculate the total index.

                    auto totalIndex{indexFirstVertexOfMesh + mesh.indices[index]};

                    // Add the total index to the indices vector.

                    indicesVector.push_back(totalIndex);
                }

                // Update the index of the first vertex of the next mesh.

                indexFirstVertexOfMesh += mesh.vertices.size();
            }

            // Calculate the number of vertices and indices.

            constexpr auto k_floatsPerVertex{8};

            auto verticesCount{verticesVector.size() / k_floatsPerVertex};

            auto indicesCount{indicesVector.size()};

            // Upload the indices to the index buffer object.

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesVector.data()[0]) * indicesCount,
                         indicesVector.data(), GL_STATIC_DRAW);

            // Upload the vertices to the vertex buffer object.

            glBufferData(GL_ARRAY_BUFFER, sizeof(verticesVector.data()[0]) * 8 * verticesCount,
                         verticesVector.data(), GL_STATIC_DRAW);

            // Setup the attribute layout.

            this->SetupAttributeLayout();

            // Update the drawing operation.

            entry.verticesCount = verticesCount;

            // Cache the drawing operation.

            m_operationsCache[modelNameHash] = entry;
        }

        // Get the elevation height.

        auto elevationHeight{_<Theme0::Theme0Properties>().GetElevationHeight()};

        auto levitationHeight{_<Theme0::CreatureIndex>().GetLevitationHeight(modelNameHash)};

        // Calculate the model matrix. This matrix differs between different rendering
        // operations, even though they use the same model.

        auto modelMatrix{glm::mat4(1.0f)};

        // Translate the model to the position.

        modelMatrix = glm::translate(
            modelMatrix, glm::vec3(x, y, elevation * elevationHeight + levitationHeight));

        // Scale the model.

        modelMatrix = glm::scale(modelMatrix, glm::vec3(modelScaling));

        // Get the view matrix.

        auto viewMatrix{_<Camera>().GetViewMatrix()};

        // Get the projection matrix.

        auto projectionMatrix{_<Camera>().GetProjectionMatrix()};

        // Upload the projection matrix to the shader.

        glUniformMatrix4fv(m_layoutLocationProjectionMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);

        // Upload the model matrix to the shader.

        glUniformMatrix4fv(m_layoutLocationModelMatrix, 1, GL_FALSE, &modelMatrix[0][0]);

        // Upload the view matrix to the shader.

        glUniformMatrix4fv(m_layoutLocationViewMatrix, 1, GL_FALSE, &viewMatrix[0][0]);

        // Get the texture name and its hash.

        auto textureName{meshes.at(0).textures.at(0).path};

        auto textureNameHash{Hash(textureName)};

        // Get the texture ID.

        auto textureID{_<TextureBank>().GetTexture(textureNameHash)};

        // Bind the texture to the shader.

        glBindTexture(GL_TEXTURE_2D, textureID);

        // Get the drawing operation.

        auto &entry{m_operationsCache.at(modelNameHash)};

        // Draw the model.

        glDrawElements(GL_TRIANGLES, entry.verticesCount, GL_UNSIGNED_SHORT, nullptr);

        // Restore the state.

        this->RestoreState();
    }
}