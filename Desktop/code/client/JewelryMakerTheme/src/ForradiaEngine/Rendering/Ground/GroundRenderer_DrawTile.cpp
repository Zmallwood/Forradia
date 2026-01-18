/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GroundRenderer.hpp"
#include "ForradiaEngine/Rendering/Base/3D/Camera.hpp"
#include "ForradiaEngine/Common/General.hpp"
#include "ForradiaEngine/Assets/Textures/TextureBank.hpp"

namespace ForradiaEngine
{
    auto GroundRenderer::drawTile(int uniqueRenderID, int imageNameHash, int xCoordinate,
                                  int yCoordinate, float tileSize,
                                  const std::vector<float> &elevations, bool forceUpdate) -> void
    {
        GLuint vao{0};
        GLuint ibo{0};
        GLuint vbo{0};

        bool tileIsCached{this->drawingOperationIsCached(uniqueRenderID)};

        // If the tile is cached.
        If(tileIsCached)
        {
            auto &entry{m_operationsCache.at(uniqueRenderID)};

            vao = entry.vao;
            ibo = entry.ibo;
            vbo = entry.vbo;

            glBindVertexArray(entry.vao);
            glBindBuffer(GL_ARRAY_BUFFER, entry.vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entry.ibo);
        }
        Else
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

        If(false == tileIsCached || forceUpdate)
        {
            std::vector<Color> colors{
                Palette::getColor<hash("White")>(), Palette::getColor<hash("White")>(),
                Palette::getColor<hash("White")>(), Palette::getColor<hash("White")>()};

            // Calculate the vertices without normals.
            auto verticesNoNormals{GroundRenderer::calcTileVerticesNoNormals(
                xCoordinate, yCoordinate, tileSize, elevations, colors)};

            auto verticesCount{4};
            auto indicesCount{4};

            // Calculate the vertices with normals.
            auto verticesVector{GroundRenderer::calcTileVerticesWithNormals(verticesNoNormals)};

            constexpr int k_numFloatsPerVertex{11};

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         static_cast<long>(sizeof(k_indices[0])) * indicesCount, k_indices.data(),
                         GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         static_cast<long>(sizeof(verticesVector[0])) * k_numFloatsPerVertex *
                             verticesCount,
                         verticesVector.data(), GL_STATIC_DRAW);

            this->setupAttributeLayout();
        }

        // Calculate the MVP matrix.
        auto modelMatrix{glm::mat4(1.0F)};
        auto viewMatrix{Camera::instance().getViewMatrix()};
        auto projectionMatrix{Camera::getProjectionMatrix()};
        auto mvpMatrix{projectionMatrix * viewMatrix * modelMatrix};

        // Upload the MVP matrix to the shader.
        glUniformMatrix4fv(m_layoutLocationMVP, 1, GL_FALSE, &mvpMatrix[0][0]);

        auto textureID{TextureBank::instance().getTexture(imageNameHash)};
        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, nullptr);
    }
}
