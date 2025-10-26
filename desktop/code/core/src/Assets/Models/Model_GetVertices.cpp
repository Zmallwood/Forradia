//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Model.hpp"

namespace Forradia
{
    Vector<GLMVertex>
    Model::GetVertices(aiMesh *mesh,
                       aiMatrix4x4 transformation)
    {
        Vector<GLMVertex> vertices;

        for (unsigned int i = 0; i < mesh->mNumVertices;
             i++)
        {
            GLMVertex vertex;

            glm::vec3 vector3;

            aiVector3D v{transformation *
                         mesh->mVertices[i]};

            // Vertices.
            vector3.x = v.x;
            vector3.y = v.y;
            vector3.z = v.z;

            vertex.position = vector3;

            // Normals.
            if (mesh->mNormals)
            {
                vector3.x = mesh->mNormals[i].x;
                vector3.y = mesh->mNormals[i].y;
                vector3.z = mesh->mNormals[i].z;

                vertex.normal = vector3;
            }

            // Texture coordinates.
            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vector2;

                vector2.x = mesh->mTextureCoords[0][i].x;
                vector2.y = mesh->mTextureCoords[0][i].y;

                vertex.uv = vector2;
            }
            else
            {
                vertex.uv = glm::vec2(0, 0);
            }

            vertices.push_back(vertex);
        }

        return vertices;
    }
}