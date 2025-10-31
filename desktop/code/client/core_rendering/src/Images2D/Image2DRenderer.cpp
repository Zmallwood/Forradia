//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Image2DRenderer.hpp"

#include "ShaderProgram.hpp"

#include "SDLDevice.hpp"

#include "Textures/TextureBank.hpp"

namespace Forradia
{
    void Image2DRenderer::Cleanup()
    {
        for (auto &entryLevel1 : m_operationsCache)
        {
            for (auto &entryLevel2 : entryLevel1.second)
            {
                for (auto &entryLevel3 : entryLevel2.second)
                {
                    glDeleteVertexArrays(
                        1, &entryLevel3.second.vao);

                    glDeleteBuffers(
                        1, &entryLevel3.second.ibo);

                    glDeleteBuffers(
                        1, &entryLevel3.second.vbo);
                }
            }
        }

        glUseProgram(0);
    }

    void Image2DRenderer::SetupState() const
    {
        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width,
                   canvasSize.height);

        glUseProgram(GetShaderProgram()->GetProgramID());

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Image2DRenderer::ResetState() const
    {
        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Image2DRenderer::DrawImageByName(
        StringView imageName, float x, float y, float width,
        float height)
    {
        this->DrawImageByHash(Hash(imageName), x, y, width,
                              height);
    }

    void Image2DRenderer::DrawImageByHash(
        int imageNameHash, float x, float y, float width,
        float height, bool useOperationsCache)
    {
        auto textureID{
            _<TextureBank>().GetTexture(imageNameHash)};

        this->DrawImageByTextureID(textureID, x, y, width,
                                   height,
                                   useOperationsCache);
    }

    void Image2DRenderer::DrawImageAutoHeight(
        StringView imageName, float x, float y, float width)
    {
        auto hash{Forradia::Hash(imageName)};

        auto imageDimensions{
            _<TextureBank>().GetTextureDimensions(hash)};

        if (imageDimensions.width <= 0 ||
            imageDimensions.height <= 0)
        {
            return;
        }

        auto canvasAspectRatio{
            CalcAspectRatio(_<SDLDevice>().GetWindow())};

        auto imageAspectRatio{
            CFloat(imageDimensions.width) /
            imageDimensions.height};

        auto height{width / imageAspectRatio *
                    canvasAspectRatio};

        this->DrawImageByHash(hash, x, y, width, height);
    }
}