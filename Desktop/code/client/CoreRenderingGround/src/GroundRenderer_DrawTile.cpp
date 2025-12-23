/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "3D/Camera.hpp"
#include "GroundRenderer.hpp"
#include "Hash.hpp"
#include "Textures/TextureBank.hpp"

namespace Forradia
{
    auto GroundRenderer::DrawTile(int uniqueRenderID, int imageNameHash, int xCoordinate,
                                  int yCoordinate, float tileSize,
                                  const std::vector<float> &elevations, bool forceUpdate) -> void
    {
        GLuint vao{0};
        GLuint ibo{0};
        GLuint vbo{0};

        bool tileIsCached{this->DrawingOperationIsCached(uniqueRenderID)};

        // If the tile is cached.
        if (tileIsCached)
        {
            auto &entry{m_operationsCache.at(uniqueRenderID)};

            vao = entry.vao;
            ibo = entry.ibo;
            vbo = entry.vbo;

            glBindVertexArray(entry.vao);
            glBindBuffer(GL_ARRAY_BUFFER, entry.vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entry.ibo);
        }
        else
        {
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ibo);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            GroundRenderingOperation entry;
            entry.vao = vao;
            entry.ibo = ibo;
            entry.vbo = vbo;

            m_operationsCache[uniqueRenderID] = entry;
        }

        if (false == tileIsCached || forceUpdate)
        {
            std::vector<Color> colors{
                Palette::GetColor<Hash("White")>(), Palette::GetColor<Hash("White")>(),
                Palette::GetColor<Hash("White")>(), Palette::GetColor<Hash("White")>()};

            // Calculate the vertices without normals.
            auto verticesNoNormals{GroundRenderer::CalcTileVerticesNoNormals(
                xCoordinate, yCoordinate, tileSize, elevations, colors)};

            auto verticesCount{4};
            auto indicesCount{4};

            // Calculate the vertices with normals.
            auto verticesVector{GroundRenderer::CalcTileVerticesWithNormals(verticesNoNormals)};

            constexpr int k_numFlotsPerVertex{11};

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(k_indices[0]) * indicesCount,
                         k_indices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(verticesVector[0]) * k_numFlotsPerVertex * verticesCount,
                         verticesVector.data(), GL_STATIC_DRAW);

            this->SetupAttributeLayout();
        }

        // Calculate the MVP matrix.
        auto modelMatrix{glm::mat4(1.0F)};
        auto viewMatrix{Camera::Instance().GetViewMatrix()};
        auto projectionMatrix{Camera::GetProjectionMatrix()};
        auto mvpMatrix{projectionMatrix * viewMatrix * modelMatrix};

        // Upload the MVP matrix to the shader.
        glUniformMatrix4fv(m_layoutLocationMVP, 1, GL_FALSE, &mvpMatrix[0][0]);

        auto textureID{TextureBank::Instance().GetTexture(imageNameHash)};
        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, nullptr);
    }
}
