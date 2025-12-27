/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GroundRenderer.hpp"
    
    #include "ForradiaEngine/Common/Utilities.hpp"
// clang-format on

namespace ForradiaEngine
{
    auto GroundRenderer::calcTileNormals(const std::vector<float> &verticesNoNormals)
        -> std::vector<glm::vec3>
    {
        constexpr size_t k_vertexStride = 8;
        constexpr size_t k_requiredVertices = 9;
        constexpr size_t k_minArraySize = k_requiredVertices * k_vertexStride;

        // Check if the vertex data is sufficient, cancel if not.
        if (verticesNoNormals.size() < k_minArraySize)
            throw std::invalid_argument("Insufficient vertex data.");

        // Create a map to store the vertices with positions only. This will be used to
        // calculate the normals.
        std::unordered_map<int, std::unordered_map<int, glm::vec3>> coords;

        // Loop through the vertices and store them in the map.
        for (auto yIdx = 0; yIdx < 3; yIdx++)
        {
            for (auto xIdx = 0; xIdx < 3; xIdx++)
            {
                // Calculate the index of the vertex.
                auto idx{yIdx * 3 + xIdx};

                // Get the vertex coordinates.
                auto vertX{verticesNoNormals[idx * k_vertexStride + 0]};
                auto vertY{verticesNoNormals[idx * k_vertexStride + 1]};
                auto vertZ{verticesNoNormals[idx * k_vertexStride + 2]};

                // Store the vertex coordinates in the map.
                coords[xIdx][yIdx] = glm::vec3{vertX, vertY, vertZ};
            }
        }

        // Calculate the normals.
        auto normal00{computeNormal(coords[1][0], coords[0][0], coords[0][1])};
        auto normal10{computeNormal(coords[2][0], coords[1][0], coords[1][1])};
        auto normal11{computeNormal(coords[2][1], coords[1][1], coords[1][2])};
        auto normal01{computeNormal(coords[1][1], coords[0][1], coords[0][2])};

        // Invert the z-component of the normals.
        normal00.z *= -1.0F;
        normal10.z *= -1.0F;
        normal11.z *= -1.0F;
        normal01.z *= -1.0F;

        // Group the normals and return them.
        auto normals{std::vector<glm::vec3>{normal00, normal10, normal11, normal01}};

        return normals;
    }
}
