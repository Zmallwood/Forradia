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

        // To contain the vertex array object, index buffer
        // object and vertex buffer object.

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        // Get the model and its meshes from the model bank.

        auto model{_<ModelBank>().GetModel(modelNameHash)};

        auto &meshes{model->GetMeshesRef()};

        // If the drawing operation is cached.
        //
        // Note: For this renderer the modelNameHash can be
        // used as a key since what changes between
        // different rendering operations is the model
        // matrix, not the vertex data (which is the case
        // for the other renderers).

        if (this->DrawingOperationIsCached(modelNameHash))
        {
            // Get the cached drawing operation.

            auto &entry{
                m_operationsCache.at(modelNameHash)};

            // Get the vertex array object, index buffer
            // object and vertex buffer object.

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
            // Generate the vertex array object, index
            // buffer object and vertex buffer object.

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

            // To contain the index of the first vertex of
            // the next mesh.

            auto indexFirstVertexOfMesh{0};

            // For each mesh.

            for (auto &mesh : meshes)
            {
                // For each vertex.

                for (auto &vertex : mesh.vertices)
                {
                    // Add position.

                    verticesVector.push_back(
                        vertex.position.x * k_modelScale);

                    verticesVector.push_back(
                        vertex.position.y * k_modelScale);

                    verticesVector.push_back(
                        vertex.position.z * k_modelScale);

                    // Add normal.

                    verticesVector.push_back(
                        vertex.normal.x);

                    verticesVector.push_back(
                        vertex.normal.y);

                    verticesVector.push_back(
                        vertex.normal.z);

                    // Add texture coordinates.

                    verticesVector.push_back(vertex.uv.x);

                    verticesVector.push_back(vertex.uv.y);
                }

                // For each index of the mesh.

                for (auto &index : mesh.indices)
                {
                    // Calculate the total index.

                    auto totalIndex{indexFirstVertexOfMesh +
                                    mesh.indices[index]};

                    // Add the total index to the indices
                    // vector.

                    indicesVector.push_back(totalIndex);
                }

                // Update the index of the first vertex of
                // the next mesh.

                indexFirstVertexOfMesh +=
                    mesh.vertices.size();
            }

            // Calculate the number of vertices and indices.

            constexpr auto k_floatsPerVertex{8};

            auto verticesCount{verticesVector.size() /
                               k_floatsPerVertex};

            auto indicesCount{indicesVector.size()};

            // Upload the indices to the index buffer
            // object.

            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(indicesVector.data()[0]) *
                             indicesCount,
                         indicesVector.data(),
                         GL_STATIC_DRAW);

            // Upload the vertices to the vertex buffer
            // object.

            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(verticesVector.data()[0]) *
                             8 * verticesCount,
                         verticesVector.data(),
                         GL_STATIC_DRAW);

            // Setup the attribute layout.

            this->SetupAttributeLayout();

            // Update the drawing operation.

            entry.verticesCount = verticesCount;

            // Cache the drawing operation.

            m_operationsCache[modelNameHash] = entry;
        }

        // Calculate the model matrix. This matrix differs
        // between different rendering operations, even
        // though they use the same model.

        auto modelMatrix{glm::translate(
            glm::mat4(1.0f),
            glm::vec3(x, y, elevation * elevationHeight))};

        // Get the view matrix.

        auto viewMatrix{_<Camera>().GetViewMatrix()};

        // Get the projection matrix.

        auto projectionMatrix{
            _<Camera>().GetProjectionMatrix()};

        // Get the matrix projection location.

        auto matrixProjection{glGetUniformLocation(
            GetShaderProgram()->GetProgramID(),
            "projection")};

        // Upload the projection matrix to the shader.

        glUniformMatrix4fv(matrixProjection, 1, GL_FALSE,
                           &projectionMatrix[0][0]);

        // Get the matrix model location.

        auto matrixModel{glGetUniformLocation(
            GetShaderProgram()->GetProgramID(), "model")};

        // Upload the model matrix to the shader.

        glUniformMatrix4fv(matrixModel, 1, GL_FALSE,
                           &modelMatrix[0][0]);

        // Get the matrix view location.

        auto matrixView{glGetUniformLocation(
            GetShaderProgram()->GetProgramID(), "view")};

        // Upload the view matrix to the shader.

        glUniformMatrix4fv(matrixView, 1, GL_FALSE,
                           &viewMatrix[0][0]);

        // Get the texture name and its hash.

        auto textureName{meshes.at(0).textures.at(0).path};

        auto textureNameHash{Hash(textureName)};

        // Get the texture ID.

        auto textureID{
            _<TextureBank>().GetTexture(textureNameHash)};

        // Bind the texture to the shader.

        glBindTexture(GL_TEXTURE_2D, textureID);

        // Get the drawing operation.

        auto &entry{m_operationsCache.at(modelNameHash)};

        // Draw the model.

        glDrawElements(GL_TRIANGLES, entry.verticesCount,
                       GL_UNSIGNED_SHORT, nullptr);

        this->RestoreState();
    }
}