/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ErrorUtilities.hpp"
#include "Model.hpp"

namespace Forradia {
    auto Model::GetVertices(aiMesh *mesh, aiMatrix4x4 transformation) -> std::vector<GLMVertex> {
        if (mesh == nullptr) {
            PrintError("mesh is nullptr");
            return {};
        }

        std::vector<GLMVertex> vertices;

        // Iterate over all vertices.
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            GLMVertex vertex;
            glm::vec3 position;

            // Get the transformed vertex position.
            auto verts{transformation * mesh->mVertices[i]};

            // Set the position coordinates.
            position.x = verts.x;
            position.y = verts.y;
            position.z = verts.z;

            vertex.position = position;

            // If there are normals.
            if (mesh->mNormals != nullptr) {
                glm::vec3 normal;

                // Set the normal coordinates.
                normal.x = mesh->mNormals[i].x;
                normal.y = mesh->mNormals[i].y;
                normal.z = mesh->mNormals[i].z;

                vertex.normal = normal;
            }

            // If there are texture coordinates.
            if (mesh->mTextureCoords[0] != nullptr) {
                glm::vec2 texCoords;

                // Set the texture coordinates.
                texCoords.x = mesh->mTextureCoords[0][i].x;
                texCoords.y = mesh->mTextureCoords[0][i].y;

                vertex.uv = texCoords;
            } else {
                // In case there are no texture coordinates, set them to zero.
                vertex.uv = glm::vec2(0, 0);
            }

            vertices.push_back(vertex);
        }
        return vertices;
    }
}
