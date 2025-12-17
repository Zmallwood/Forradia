/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Model.hpp"
#include "StdAfx.hpp"

namespace Forradia {
auto Model::GetVertices(aiMesh *mesh, aiMatrix4x4 transformation) const -> Vector<GLMVertex> {
  Vector<GLMVertex> vertices;

  // Iterate over all vertices.
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    GLMVertex vertex;
    glm::vec3 position;

    // Get the transformed vertex position.
    auto v{transformation * mesh->mVertices[i]};

    // Set the position coordinates.
    position.x = v.x;
    position.y = v.y;
    position.z = v.z;

    vertex.position = position;

    // If there are normals.
    if (mesh->mNormals) {
      glm::vec3 normal;

      // Set the normal coordinates.
      normal.x = mesh->mNormals[i].x;
      normal.y = mesh->mNormals[i].y;
      normal.z = mesh->mNormals[i].z;

      vertex.normal = normal;
    }

    // If there are texture coordinates.
    if (mesh->mTextureCoords[0]) {
      glm::vec2 uv;

      // Set the texture coordinates.
      uv.x = mesh->mTextureCoords[0][i].x;
      uv.y = mesh->mTextureCoords[0][i].y;

      vertex.uv = uv;
    } else {
      // In case there are no texture coordinates, set them to zero.
      vertex.uv = glm::vec2(0, 0);
    }

    vertices.push_back(vertex);
  }
  return vertices;
}
}
