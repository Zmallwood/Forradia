//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GroundRenderer.hpp"

namespace Forradia
{
    Vector<float>
    GroundRenderer::CalcTileVerticesWithNormals(
        const Vector<float> &verticesNoNormals)
    {
        Vector<float> verticesVector;

        Vector<glm::vec3> normals{
            this->CalcTileNormals(verticesNoNormals)};

        constexpr int k_vertexStride{8};

        auto fnAddVertex{
            [&](int i, int j)
            {
                verticesVector.push_back(
                    verticesNoNormals[i * k_vertexStride +
                                      0]);

                verticesVector.push_back(
                    verticesNoNormals[i * k_vertexStride +
                                      1]);

                verticesVector.push_back(
                    verticesNoNormals[i * k_vertexStride +
                                      2]);

                verticesVector.push_back(
                    verticesNoNormals[i * k_vertexStride +
                                      3]);

                verticesVector.push_back(
                    verticesNoNormals[i * k_vertexStride +
                                      4]);

                verticesVector.push_back(
                    verticesNoNormals[i * k_vertexStride +
                                      5]);

                verticesVector.push_back(
                    verticesNoNormals[i * k_vertexStride +
                                      6]);

                verticesVector.push_back(
                    verticesNoNormals[i * k_vertexStride +
                                      7]);

                verticesVector.push_back(normals.at(j).x);

                verticesVector.push_back(normals.at(j).y);

                verticesVector.push_back(normals.at(j).z);
            }};

        fnAddVertex(0, 0);

        fnAddVertex(1, 1);

        fnAddVertex(4, 2);

        fnAddVertex(3, 3);

        return verticesVector;
    }
}