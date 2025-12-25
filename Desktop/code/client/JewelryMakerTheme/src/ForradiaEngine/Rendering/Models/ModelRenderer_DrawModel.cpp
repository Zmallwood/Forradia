/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ForradiaEngine/Assets/Models/Construction/Model.hpp"
    #include "ForradiaEngine/Assets/Models/ModelBank.hpp"
    #include "ForradiaEngine/Assets/Textures/TextureBank.hpp"
    #include "ForradiaEngine/Common/General/Hash.hpp"
    #include "ModelRenderer.hpp"
    #include "ForradiaEngine/Rendering/Base/3D/Camera.hpp"
    #include <glm/gtx/transform.hpp>
// clang-format on

namespace ForradiaEngine
{
    auto ModelRenderer::drawModel(int modelNameHash, float xPos, float yPos, float elevation,
                                  float modelScaling, float elevationHeight, float levitationHeight)
        -> void
    {
        this->setupState();

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto model{ModelBank::instance().getModel(modelNameHash)};
        const auto &meshes{model->getMeshesRef()};

        // If the drawing operation is cached.
        if (this->drawingOperationIsCached(modelNameHash))
        {
            auto &entry{m_operationsCache.at(modelNameHash)};

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

            std::vector<unsigned short> indicesVector;
            std::vector<float> verticesVector;

            // To contain the index of the first vertex of the next mesh.
            auto indexFirstVertexOfMesh{0};

            float totalModelScaling{k_globalModelScaling * modelScaling};

            // For each mesh.
            for (const auto &mesh : meshes)
            {
                // For each vertex.
                for (const auto &vertex : mesh.vertices)
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
                for (const auto &index : mesh.indices)
                {
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

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesVector[0]) * indicesCount,
                         indicesVector.data(), GL_STATIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(verticesVector[0]) * k_floatsPerVertex * verticesCount,
                         verticesVector.data(), GL_STATIC_DRAW);

            this->setupAttributeLayout();

            entry.verticesCount = verticesCount;

            m_operationsCache[modelNameHash] = entry;
        }

        // Calculate the model matrix. This matrix differs between different rendering
        // operations, even though they use the same model.
        auto modelMatrix{glm::mat4(1.0F)};

        // Translate the model to the position.
        modelMatrix = glm::translate(
            modelMatrix, glm::vec3(xPos, yPos, elevation * elevationHeight + levitationHeight));

        modelMatrix = glm::scale(modelMatrix, glm::vec3(modelScaling));

        auto viewMatrix{Camera::instance().getViewMatrix()};
        auto projectionMatrix{Camera::getProjectionMatrix()};

        glUniformMatrix4fv(m_layoutLocationProjectionMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
        glUniformMatrix4fv(m_layoutLocationModelMatrix, 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(m_layoutLocationViewMatrix, 1, GL_FALSE, &viewMatrix[0][0]);

        auto textureName{meshes.at(0).textures.at(0).path};
        auto textureNameHash{hash(textureName)};

        auto textureID{TextureBank::instance().getTexture(textureNameHash)};
        glBindTexture(GL_TEXTURE_2D, textureID);

        auto &entry{m_operationsCache.at(modelNameHash)};

        glDrawElements(GL_TRIANGLES, entry.verticesCount, GL_UNSIGNED_SHORT, nullptr);

        ModelRenderer::restoreState();
    }
}
