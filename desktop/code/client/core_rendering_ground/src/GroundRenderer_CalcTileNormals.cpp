//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GroundRenderer.hpp"

namespace Forradia
{
    Vector<glm::vec3> GroundRenderer::CalcTileNormals(
        const Vector<float> &verticesNoNormals)
    {
        constexpr size_t k_vertexStride = 8;

        constexpr size_t k_requiredVertices = 9;

        constexpr size_t k_minArraySize =
            k_requiredVertices * k_vertexStride;

        if (verticesNoNormals.size() < k_minArraySize)
        {
            throw std::invalid_argument(
                "Insufficient vertex data.");
        }

        std::map<int, std::map<int, glm::vec3>> v;

        for (auto y = 0; y < 3; y++)
        {
            for (auto x = 0; x < 3; x++)
            {
                auto i{y * 3 + x};

                auto vX{
                    verticesNoNormals[i * k_vertexStride +
                                      0]};
                auto vY{
                    verticesNoNormals[i * k_vertexStride +
                                      1]};
                auto vZ{
                    verticesNoNormals[i * k_vertexStride +
                                      2]};

                v[x][y] = glm::vec3{vX, vY, vZ};
            }
        }

        auto normal00{
            ComputeNormal(v[1][0], v[0][0], v[0][1])};

        auto normal10{
            ComputeNormal(v[2][0], v[1][0], v[1][1])};

        auto normal11{
            ComputeNormal(v[2][1], v[1][1], v[1][2])};

        auto normal01{
            ComputeNormal(v[1][1], v[0][1], v[0][2])};

        normal00.z *= -1.0f;
        normal10.z *= -1.0f;
        normal11.z *= -1.0f;
        normal01.z *= -1.0f;

        Vector<glm::vec3> normals;

        normals.push_back(normal00);
        normals.push_back(normal10);
        normals.push_back(normal11);
        normals.push_back(normal01);

        return normals;
    }
}