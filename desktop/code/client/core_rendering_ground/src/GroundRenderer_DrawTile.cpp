//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GroundRenderer.hpp"

#include "ShaderProgram.hpp"

#include "Textures/TextureBank.hpp"

#include "SDLDevice.hpp"

#include "3D/Camera.hpp"

namespace Forradia
{
    void GroundRenderer::Reset()
    {
        this->Cleanup();

        m_operationsCache.clear();
    }

    void GroundRenderer::DrawTile(
        int uniqueRenderID, int imageNameHash,
        int xCoordinate, int yCoordinate, float tileSize,
        const Vector<float> &elevations,
        float elevationHeight, bool forceUpdate)
    {
        auto textureID{
            _<TextureBank>().GetTexture(imageNameHash)};

        // TODO: Set viewport and configure blending etc.
        // outside the per-tile-loop as settings on every
        // tile draw is inefficient.

        this->SetupState();

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        bool fillBuffers{false};

        if (this->DrawingOperationIsCached(uniqueRenderID))
        {
            auto &entry =
                m_operationsCache.at(uniqueRenderID);

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
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

            fillBuffers = true;
        }

        if (fillBuffers || forceUpdate)
        {
            auto verticesNoNormals{
                this->CalcTileVerticesNoNormals(
                    xCoordinate, yCoordinate, tileSize,
                    elevations, elevationHeight)};

            auto verticesCount{4};

            auto indicesCount{4};

            auto verticesVector{
                this->CalcTileVerticesWithNormals(
                    verticesNoNormals)};

            auto vertices{verticesVector.data()};

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(k_indices[0]) *
                             indicesCount,
                         k_indices, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(vertices[0]) * 11 *
                             verticesCount,
                         vertices, GL_STATIC_DRAW);

            this->SetupAttributeLayout();
        }

        glm::mat4 modelMatrix = glm::mat4(1.0f);

        auto viewMatrix{_<Camera>().GetViewMatrix()};

        auto projectionMatrix{
            _<Camera>().GetProjectionMatrix()};

        glm::mat4 finalMatrix =
            projectionMatrix * viewMatrix * modelMatrix;

        GLuint mvpMatrixID = glGetUniformLocation(
            GetShaderProgram()->GetProgramID(), "MVP");

        glUniformMatrix4fv(mvpMatrixID, 1, GL_FALSE,
                           &finalMatrix[0][0]);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLE_FAN, 4,
                       GL_UNSIGNED_SHORT, nullptr);

        this->RestoreState();
    }

    bool GroundRenderer::DrawingOperationIsCached(
        int uniqueRenderID) const
    {
        return m_operationsCache.contains(uniqueRenderID);
    }
}