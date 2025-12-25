/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GroundRenderer.hpp"
// clang-format on

namespace Forradia
{
    auto GroundRenderer::calcTileVerticesWithNormals(const std::vector<float> &verticesNoNormals)
        -> std::vector<float>
    {
        // Create a vector to store the vertices consisting of only floats.
        std::vector<float> verticesFloatsVector;

        auto normals{GroundRenderer::calcTileNormals(verticesNoNormals)};

        constexpr auto k_vertexStride{8};

        // Define a lambda function to add a vertex to the floats vector.
        auto fnAddVertexToFloatsVector{
            [&](int vertexIndex, int normalsIndex)
            {
                // Add the vertex coordinates to the floats vector.

                constexpr int k_xPos{0};
                constexpr int k_yPos{1};
                constexpr int k_zPos{2};
                constexpr int k_redPos{3};
                constexpr int k_greenPos{4};
                constexpr int k_bluePos{5};
                constexpr int k_uPos{6};
                constexpr int k_vPos{7};

                // Position.
                verticesFloatsVector.push_back(
                    verticesNoNormals[vertexIndex * k_vertexStride + k_xPos]);
                verticesFloatsVector.push_back(
                    verticesNoNormals[vertexIndex * k_vertexStride + k_yPos]);
                verticesFloatsVector.push_back(
                    verticesNoNormals[vertexIndex * k_vertexStride + k_zPos]);

                // Color.
                verticesFloatsVector.push_back(
                    verticesNoNormals[vertexIndex * k_vertexStride + k_redPos]);
                verticesFloatsVector.push_back(
                    verticesNoNormals[vertexIndex * k_vertexStride + k_greenPos]);
                verticesFloatsVector.push_back(
                    verticesNoNormals[vertexIndex * k_vertexStride + k_bluePos]);

                // Texture coordinates (UVs).
                verticesFloatsVector.push_back(
                    verticesNoNormals[vertexIndex * k_vertexStride + k_uPos]);
                verticesFloatsVector.push_back(
                    verticesNoNormals[vertexIndex * k_vertexStride + k_vPos]);

                // Normals.
                verticesFloatsVector.push_back(normals.at(normalsIndex).x);
                verticesFloatsVector.push_back(normals.at(normalsIndex).y);
                verticesFloatsVector.push_back(normals.at(normalsIndex).z);
            }};

        // Call the lambda function for the four vertices in the order of the indices.
        fnAddVertexToFloatsVector(0, 0);
        fnAddVertexToFloatsVector(1, 1);
        fnAddVertexToFloatsVector(4, 2);
        fnAddVertexToFloatsVector(3, 3);

        // Return the resulting vertex vector consisting of only floats.
        return verticesFloatsVector;
    }
}
