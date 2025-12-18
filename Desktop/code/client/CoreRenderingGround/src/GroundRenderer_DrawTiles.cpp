/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "3D/Camera.hpp"
#include "GroundRenderer.hpp"
#include "StdAfx.hpp"
#include "Textures/TextureBank.hpp"

namespace Forradia {
  auto GroundRenderer::DrawTiles(const Vector<TileData> &tiles) -> void {
    auto uniqueRenderID{tiles.at(0).uniqueRenderID};
    auto forceUpdate{false};

    for (auto &tile : tiles) {
      if (tile.forceUpdate) {
        forceUpdate = true;
        break;
      }
    }

    GroundRenderingGroupOperation groupOperation;

    bool tileIsCached{m_groupOperationsCache.contains(uniqueRenderID)};

    // If the tile is not cached or the force update flag is set.
    if (false == tileIsCached || forceUpdate) {
      std::map<int, Vector<TileData>> tileDataByTexture;

      for (auto i = 0; i < tiles.size(); i++) {
        auto textureNameHash = tiles.at(i).imageNameHash;

        if (!tileDataByTexture.contains(textureNameHash))
          tileDataByTexture[textureNameHash] = Vector<TileData>();

        tileDataByTexture[textureNameHash].push_back(tiles.at(i));
      }

      std::map<int, TileDrawGroup> tilesByTexture;

      for (auto &entry : tileDataByTexture) {
        TileDrawGroup group;

        auto textureNameHash = entry.first;
        auto &tileData = entry.second;

        glGenVertexArrays(1, &group.vao);
        glGenBuffers(1, &group.vbo);
        glGenBuffers(1, &group.ibo);

        glBindVertexArray(group.vao);
        glBindBuffer(GL_ARRAY_BUFFER, group.vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group.ibo);

        unsigned short vertexOffset{0};

        Vector<float> combinedVertices;
        Vector<unsigned short> combinedIndices;

        for (auto tile : tileData) {
          auto xCoordinate{tile.xCoordinate};
          auto yCoordinate{tile.yCoordinate};

          auto tileSize{tile.tileSize};

          auto elevations{tile.elevations};

          // Calculate the vertices without normals.
          auto verticesNoNormals{this->CalcTileVerticesNoNormals(
              xCoordinate, yCoordinate, tileSize, elevations,
              {tile.color00, tile.color10, tile.color11, tile.color01})};

          auto verticesCount{4};
          auto indicesCount{6};

          // Calculate the vertices with normals.
          auto verticesVector{this->CalcTileVerticesWithNormals(verticesNoNormals)};

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

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group.ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(combinedIndices[0]) * combinedIndices.size(),
                     combinedIndices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, group.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(combinedVertices[0]) * combinedVertices.size(),
                     combinedVertices.data(), GL_STATIC_DRAW);

        this->SetupAttributeLayout();

        group.combinedIndicesCount = combinedIndices.size();

        tilesByTexture.insert({textureNameHash, group});
      }

      groupOperation.tilesByTexture = tilesByTexture;

      m_groupOperationsCache[uniqueRenderID] = groupOperation;
    } else {
      groupOperation = m_groupOperationsCache.at(uniqueRenderID);
    }

    // Calculate the MVP matrix.
    auto modelMatrix{glm::mat4(1.0f)};
    auto viewMatrix{_<Camera>().GetViewMatrix()};
    auto projectionMatrix{_<Camera>().GetProjectionMatrix()};
    auto mvpMatrix{projectionMatrix * viewMatrix * modelMatrix};

    // Upload the MVP matrix to the shader.
    glUniformMatrix4fv(m_layoutLocationMVP, 1, GL_FALSE, &mvpMatrix[0][0]);

    for (auto &entry : groupOperation.tilesByTexture) {
      auto imageNameHash = entry.first;

      if (imageNameHash == 0)
        continue;

      auto group = entry.second;

      auto textureID{_<TextureBank>().GetTexture(imageNameHash)};
      glBindTexture(GL_TEXTURE_2D, textureID);

      glBindVertexArray(group.vao);
      glBindBuffer(GL_ARRAY_BUFFER, group.vbo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group.ibo);

      glDrawElements(GL_TRIANGLES, group.combinedIndicesCount, GL_UNSIGNED_SHORT, nullptr);
    }
  }
}
