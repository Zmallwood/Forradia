//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GroundRenderer.hpp"

namespace AAK
{
    namespace Forradia
    {
        Vector<float>
        GroundRenderer::CalcTileVerticesWithNormals(const Vector<float> &verticesNoNormals) const
        {
            // Create a vector to store the vertices consisting of only floats.

            Vector<float> verticesFloatsVector;

            // Get the calculated normals.

            auto normals{this->CalcTileNormals(verticesNoNormals)};

            // Define the vertex stride.

            constexpr auto k_vertexStride{8};

            // Define a lambda function to add a vertex to the floats vector.

            auto fnAddVertexToFloatsVector{
                [&](int vertexIndex, int normalsIndex)
                {
                    // Add the vertex coordinates to the floats vector.

                    // Position.

                    verticesFloatsVector.push_back(
                        verticesNoNormals[vertexIndex * k_vertexStride + 0]);

                    verticesFloatsVector.push_back(
                        verticesNoNormals[vertexIndex * k_vertexStride + 1]);

                    verticesFloatsVector.push_back(
                        verticesNoNormals[vertexIndex * k_vertexStride + 2]);

                    // Color.

                    verticesFloatsVector.push_back(
                        verticesNoNormals[vertexIndex * k_vertexStride + 3]);

                    verticesFloatsVector.push_back(
                        verticesNoNormals[vertexIndex * k_vertexStride + 4]);

                    verticesFloatsVector.push_back(
                        verticesNoNormals[vertexIndex * k_vertexStride + 5]);

                    // Texture coordinates (UVs).

                    verticesFloatsVector.push_back(
                        verticesNoNormals[vertexIndex * k_vertexStride + 6]);

                    verticesFloatsVector.push_back(
                        verticesNoNormals[vertexIndex * k_vertexStride + 7]);

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
}