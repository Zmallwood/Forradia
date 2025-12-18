/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GroundRenderer.hpp"
#include "StdAfx.hpp"

namespace Forradia {
  auto GroundRenderer::CalcTileNormals(const Vector<float> &verticesNoNormals) const
      -> Vector<glm::vec3> {
    constexpr size_t k_vertexStride = 8;
    constexpr size_t k_requiredVertices = 9;
    constexpr size_t k_minArraySize = k_requiredVertices * k_vertexStride;

    // Check if the vertex data is sufficient, cancel if not.
    if (verticesNoNormals.size() < k_minArraySize)
      throw std::invalid_argument("Insufficient vertex data.");

    // Create a map to store the vertices with positions only. This will be used to
    // calculate the normals.
    std::map<int, std::map<int, glm::vec3>> v;

    // Loop through the vertices and store them in the map.
    for (auto y = 0; y < 3; y++) {
      for (auto x = 0; x < 3; x++) {
        // Calculate the index of the vertex.
        auto i{y * 3 + x};

        // Get the vertex coordinates.
        auto vX{verticesNoNormals[i * k_vertexStride + 0]};
        auto vY{verticesNoNormals[i * k_vertexStride + 1]};
        auto vZ{verticesNoNormals[i * k_vertexStride + 2]};

        // Store the vertex coordinates in the map.
        v[x][y] = glm::vec3{vX, vY, vZ};
      }
    }

    // Calculate the normals.
    auto normal00{ComputeNormal(v[1][0], v[0][0], v[0][1])};
    auto normal10{ComputeNormal(v[2][0], v[1][0], v[1][1])};
    auto normal11{ComputeNormal(v[2][1], v[1][1], v[1][2])};
    auto normal01{ComputeNormal(v[1][1], v[0][1], v[0][2])};

    // Invert the z-component of the normals.
    normal00.z *= -1.0f;
    normal10.z *= -1.0f;
    normal11.z *= -1.0f;
    normal01.z *= -1.0f;

    // Group the normals and return them.
    auto normals{Vector<glm::vec3>{normal00, normal10, normal11, normal01}};
    return normals;
  }
}
