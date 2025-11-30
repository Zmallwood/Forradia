//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GroundRenderer.hpp"

#include "Textures/TextureBank.hpp"

#include "3D/Camera.hpp"

namespace AAK
{
    namespace Forradia
    {
        void GroundRenderer::DrawTile(int uniqueRenderID, int imageNameHash, int xCoordinate,
                                      int yCoordinate, float tileSize,
                                      const Vector<float> &elevations, bool forceUpdate)
        {
            // TODO: Set viewport and configure blending etc. outside the per-tile-loop as settings
            // on every tile draw is inefficient.

            // To be filled with the vertex array object, index buffer object and vertex buffer
            // object.

            GLuint vao{0};

            GLuint ibo{0};

            GLuint vbo{0};

            // Check if the tile is cached.

            bool tileIsCached{this->DrawingOperationIsCached(uniqueRenderID)};

            // If the tile is cached.

            if (tileIsCached)
            {
                // Get the cached entry.

                auto &entry{m_operationsCache.at(uniqueRenderID)};

                // Set the vertex array object, index buffer object and vertex buffer object.

                vao = entry.vao;

                ibo = entry.ibo;

                vbo = entry.vbo;

                // Bind them as well.

                glBindVertexArray(entry.vao);

                glBindBuffer(GL_ARRAY_BUFFER, entry.vbo);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entry.ibo);
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

                // Create a new entry and store it in the operations cache.

                GroundRenderingOperation entry;

                entry.vao = vao;

                entry.ibo = ibo;

                entry.vbo = vbo;

                m_operationsCache[uniqueRenderID] = entry;
            }

            // If the tile is not cached or the force update flag is set.

            if (false == tileIsCached || forceUpdate)
            {
                // Calculate the vertices without normals.

                auto verticesNoNormals{this->CalcTileVerticesNoNormals(xCoordinate, yCoordinate,
                                                                       tileSize, elevations)};

                // Define the number of vertices and indices.

                auto verticesCount{4};

                auto indicesCount{4};

                // Calculate the vertices with normals.

                auto verticesVector{this->CalcTileVerticesWithNormals(verticesNoNormals)};

                // Get the vertices as a float array.

                auto vertices{verticesVector.data()};

                // Bind the index buffer object.

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

                // Upload the indices to the index buffer object.

                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(k_indices[0]) * indicesCount,
                             k_indices, GL_STATIC_DRAW);

                // Bind the vertex buffer object.

                glBindBuffer(GL_ARRAY_BUFFER, vbo);

                // Upload the vertices to the vertex buffer object.

                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 11 * verticesCount, vertices,
                             GL_STATIC_DRAW);

                // Setup the attribute layout.

                this->SetupAttributeLayout();
            }

            // Calculate the MVP matrix.

            auto modelMatrix{glm::mat4(1.0f)};

            auto viewMatrix{_<Camera>().GetViewMatrix()};

            auto projectionMatrix{_<Camera>().GetProjectionMatrix()};

            auto mvpMatrix{projectionMatrix * viewMatrix * modelMatrix};

            // Upload the MVP matrix to the shader.

            glUniformMatrix4fv(m_layoutLocationMVP, 1, GL_FALSE, &mvpMatrix[0][0]);

            // Get the texture ID and bind it.

            auto textureID{_<TextureBank>().GetTexture(imageNameHash)};

            glBindTexture(GL_TEXTURE_2D, textureID);

            // Draw the tile.

            glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, nullptr);
        }
    }
}