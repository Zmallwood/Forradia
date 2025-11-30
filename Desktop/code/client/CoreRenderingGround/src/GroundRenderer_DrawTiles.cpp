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
        void GroundRenderer::DrawTiles(const Vector<TileData> &tiles)
        {
            // TODO: Set viewport and configure blending etc. outside the per-tile-loop as settings
            // on every tile draw is inefficient.

            // To be filled with the vertex array object, index buffer object and vertex buffer
            // object.

            auto uniqueRenderID{tiles.at(0).uniqueRenderID};

            auto forceUpdate{tiles.at(0).forceUpdate};

            GroundRenderingGroupOperation groupOperation;

            // Check if the tile is cached.

            bool tileIsCached{m_groupOperationsCache.contains(uniqueRenderID)};

            // If the tile is not cached or the force update flag is set.

            if (false == tileIsCached || forceUpdate)
            {
                std::map<int, Vector<TileData>> tileDataByTexture;

                for (auto i = 0; i < tiles.size(); i++)
                {
                    auto textureNameHash = tiles.at(i).imageNameHash;

                    if (!tileDataByTexture.contains(textureNameHash))
                    {
                        tileDataByTexture[textureNameHash] = Vector<TileData>();
                    }

                    tileDataByTexture[textureNameHash].push_back(tiles.at(i));
                }

                std::map<int, TileDrawGroup> tilesByTexture;

                for (auto &entry : tileDataByTexture)
                {
                    TileDrawGroup group;

                    auto textureNameHash = entry.first;

                    auto &tileData = entry.second;

                    // Generate the vertex array object, index buffer object and vertex buffer
                    // object.

                    glGenVertexArrays(1, &group.vao);

                    glGenBuffers(1, &group.vbo);

                    glGenBuffers(1, &group.ibo);

                    // Bind them as well.

                    glBindVertexArray(group.vao);

                    glBindBuffer(GL_ARRAY_BUFFER, group.vbo);

                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group.ibo);

                    unsigned short vertexOffset{0};

                    Vector<float> combinedVertices;
                    Vector<unsigned short> combinedIndices;

                    for (auto tile : tileData)
                    {
                        auto xCoordinate = tile.xCoordinate;

                        auto yCoordinate = tile.yCoordinate;

                        auto tileSize = tile.tileSize;

                        auto elevations = tile.elevations;

                        // Calculate the vertices without normals.

                        auto verticesNoNormals{this->CalcTileVerticesNoNormals(
                            xCoordinate, yCoordinate, tileSize, elevations)};

                        // Define the number of vertices and indices.

                        auto verticesCount{4};

                        auto indicesCount{6};

                        // Calculate the vertices with normals.

                        auto verticesVector{this->CalcTileVerticesWithNormals(verticesNoNormals)};

                        // Get the vertices as a float array.

                        // Add vertices to the combined buffer.
                        combinedVertices.insert(combinedVertices.end(), verticesVector.begin(),
                                                verticesVector.end());

                        // Add indices with proper offset.
                        // Convert quad (4 vertices) to 2 triangles (6 indices).
                        // Original quad indices: [0, 1, 2, 3] -> Triangles: [0,1,2] and [0,2,3]
                        combinedIndices.push_back(vertexOffset + 0);
                        combinedIndices.push_back(vertexOffset + 1);
                        combinedIndices.push_back(vertexOffset + 2);
                        combinedIndices.push_back(vertexOffset + 0);
                        combinedIndices.push_back(vertexOffset + 2);
                        combinedIndices.push_back(vertexOffset + 3);

                        // Add to the vertex offset.

                        vertexOffset += 4;
                    }

                    /// Upload indices.

                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group.ibo);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                 sizeof(combinedIndices[0]) * combinedIndices.size(),
                                 combinedIndices.data(), GL_STATIC_DRAW);

                    // Upload vertices.

                    glBindBuffer(GL_ARRAY_BUFFER, group.vbo);
                    glBufferData(GL_ARRAY_BUFFER,
                                 sizeof(combinedVertices[0]) * combinedVertices.size(),
                                 combinedVertices.data(), GL_STATIC_DRAW);

                    // Setup the attribute layout.

                    this->SetupAttributeLayout();

                    group.combinedIndicesCount = combinedIndices.size();

                    tilesByTexture.insert({textureNameHash, group});
                }

                groupOperation.tilesByTexture = tilesByTexture;

                m_groupOperationsCache[uniqueRenderID] = groupOperation;
            }
            else
            {
                groupOperation = m_groupOperationsCache.at(uniqueRenderID);
            }

            // Calculate the MVP matrix.

            auto modelMatrix{glm::mat4(1.0f)};

            auto viewMatrix{_<Camera>().GetViewMatrix()};

            auto projectionMatrix{_<Camera>().GetProjectionMatrix()};

            auto mvpMatrix{projectionMatrix * viewMatrix * modelMatrix};

            // Upload the MVP matrix to the shader.

            glUniformMatrix4fv(m_layoutLocationMVP, 1, GL_FALSE, &mvpMatrix[0][0]);

            for (auto &entry : groupOperation.tilesByTexture)
            {
                auto imageNameHash = entry.first;

                if (imageNameHash == 0)
                {
                    continue;
                }

                auto group = entry.second;

                // Get the texture ID and bind it.

                auto textureID{_<TextureBank>().GetTexture(imageNameHash)};

                glBindTexture(GL_TEXTURE_2D, textureID);

                glBindVertexArray(group.vao);

                glBindBuffer(GL_ARRAY_BUFFER, group.vbo);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group.ibo);

                // Draw the tiles.

                glDrawElements(GL_TRIANGLES, group.combinedIndicesCount, GL_UNSIGNED_SHORT,
                               nullptr);
            }
        }
    }
}