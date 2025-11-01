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
        Vector<glm::vec3> normals;

        constexpr size_t k_vertexStride = 8;
        constexpr size_t k_requiredVertices = 9;
        constexpr size_t k_minArraySize =
            k_requiredVertices * k_vertexStride;

        if (verticesNoNormals.size() < k_minArraySize)
        {
            throw std::invalid_argument(
                "Insufficient vertex data.");
        }

        auto &_00x{
            verticesNoNormals[0 * k_vertexStride + 0]};
        auto &_00y{
            verticesNoNormals[0 * k_vertexStride + 1]};
        auto &_00z{
            verticesNoNormals[0 * k_vertexStride + 2]};
        auto &_10x{
            verticesNoNormals[1 * k_vertexStride + 0]};
        auto &_10y{
            verticesNoNormals[1 * k_vertexStride + 1]};
        auto &_10z{
            verticesNoNormals[1 * k_vertexStride + 2]};
        auto &_20x{
            verticesNoNormals[2 * k_vertexStride + 0]};
        auto &_20y{
            verticesNoNormals[2 * k_vertexStride + 1]};
        auto &_20z{
            verticesNoNormals[2 * k_vertexStride + 2]};
        auto &_01x{
            verticesNoNormals[3 * k_vertexStride + 0]};
        auto &_01y{
            verticesNoNormals[3 * k_vertexStride + 1]};
        auto &_01z{
            verticesNoNormals[3 * k_vertexStride + 2]};
        auto &_11x{
            verticesNoNormals[4 * k_vertexStride + 0]};
        auto &_11y{
            verticesNoNormals[4 * k_vertexStride + 1]};
        auto &_11z{
            verticesNoNormals[4 * k_vertexStride + 2]};
        auto &_21x{
            verticesNoNormals[5 * k_vertexStride + 0]};
        auto &_21y{
            verticesNoNormals[5 * k_vertexStride + 1]};
        auto &_21z{
            verticesNoNormals[5 * k_vertexStride + 2]};
        auto &_02x{
            verticesNoNormals[6 * k_vertexStride + 0]};
        auto &_02y{
            verticesNoNormals[6 * k_vertexStride + 1]};
        auto &_02z{
            verticesNoNormals[6 * k_vertexStride + 2]};
        auto &_12x{
            verticesNoNormals[7 * k_vertexStride + 0]};
        auto &_12y{
            verticesNoNormals[7 * k_vertexStride + 1]};
        auto &_12z{
            verticesNoNormals[7 * k_vertexStride + 2]};
        auto &_22x{
            verticesNoNormals[8 * k_vertexStride + 0]};
        auto &_22y{
            verticesNoNormals[8 * k_vertexStride + 1]};
        auto &_22z{
            verticesNoNormals[8 * k_vertexStride + 2]};

        glm::vec3 v00 = {_00x, _00y, _00z};
        glm::vec3 v10 = {_10x, _10y, _10z};
        glm::vec3 v20 = {_20x, _20y, _20z};
        glm::vec3 v01 = {_01x, _01y, _01z};
        glm::vec3 v11 = {_11x, _11y, _11z};
        glm::vec3 v21 = {_21x, _21y, _21z};
        glm::vec3 v02 = {_02x, _02y, _02z};
        glm::vec3 v12 = {_12x, _12y, _12z};
        glm::vec3 v22 = {_22x, _22y, _22z};

        glm::vec3 normal00 = ComputeNormal(v10, v00, v01);
        glm::vec3 normal10 = ComputeNormal(v20, v10, v11);
        glm::vec3 normal11 = ComputeNormal(v21, v11, v12);
        glm::vec3 normal01 = ComputeNormal(v11, v01, v02);

        normal00.z *= -1.0f;
        normal10.z *= -1.0f;
        normal11.z *= -1.0f;
        normal01.z *= -1.0f;

        normals.push_back(normal00);
        normals.push_back(normal10);
        normals.push_back(normal11);
        normals.push_back(normal01);

        return normals;
    }
}