//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Model.hpp"

namespace Forradia
{
    Vector<GLMVertex> Model::GetVertices(aiMesh *mesh, aiMatrix4x4 transformation) const
    {
        // To hold the resulting vertices.

        Vector<GLMVertex> vertices;

        // Iterate over all vertices.

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            // To hold the resulting vertex.

            GLMVertex vertex;

            // To hold the resulting position for the vertex.

            glm::vec3 position;

            // Get the transformed vertex position.

            auto v{transformation * mesh->mVertices[i]};

            // Set the position coordinates.

            position.x = v.x;

            position.y = v.y;

            position.z = v.z;

            // Add the position to the vertex.

            vertex.position = position;

            // If there are normals.

            if (mesh->mNormals)
            {
                // To hold the resulting normal for the vertex.

                glm::vec3 normal;

                // Set the normal coordinates.

                normal.x = mesh->mNormals[i].x;

                normal.y = mesh->mNormals[i].y;

                normal.z = mesh->mNormals[i].z;

                // Add the normal to the vertex.

                vertex.normal = normal;
            }

            // If there are texture coordinates.

            if (mesh->mTextureCoords[0])
            {
                // To hold the resulting texture coordinates for the vertex.

                glm::vec2 uv;

                // Set the texture coordinates.

                uv.x = mesh->mTextureCoords[0][i].x;

                uv.y = mesh->mTextureCoords[0][i].y;

                // Add the texture coordinates to the vertex.

                vertex.uv = uv;
            }
            else
            {
                // In case there are no texture coordinates, set them to zero.

                vertex.uv = glm::vec2(0, 0);
            }

            // Add the vertex to the results.

            vertices.push_back(vertex);
        }

        // Return the vertices results.

        return vertices;
    }
}