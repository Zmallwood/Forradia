//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Image2DRenderer.hpp"

#include "Base/ShaderProgram.hpp"

#include "Textures/TextureBank.hpp"

#include "SDLDevice.hpp"

namespace Forradia
{
    void Image2DRenderer::Initialize()
    {
        String vertexShaderSource{
            this->GetVertexShaderSource()};

        String fragmentShaderSource{
            this->GetFragmentShaderSource()};

        m_shaderProgram = std::make_shared<ShaderProgram>(
            vertexShaderSource, fragmentShaderSource);
    }

    void Image2DRenderer::Cleanup()
    {
        for (auto &entry : m_operationsMemory)
        {
            for (auto &entry2 : entry.second)
            {
                for (auto &entry3 : entry2.second)
                {
                    glDeleteVertexArrays(
                        1, &entry3.second.vao);

                    glDeleteBuffers(1, &entry3.second.ibo);

                    glDeleteBuffers(1, &entry3.second.vbo);
                }
            }
        }

        glUseProgram(0);
    }

    void Image2DRenderer::DrawImage(int imageNameHash,
                                    float x, float y,
                                    float width,
                                    float height)
    {
        auto textureID{
            _<TextureBank>().GetTexture(imageNameHash)};

        Image2DRenderer::DrawTexture(textureID, x, y, width,
                                     height, true);
    }

    void Image2DRenderer::DrawTexture(
        GLuint textureID, float x, float y, float width,
        float height, bool useOperationsMemory)
    {
        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width,
                   canvasSize.height);

        glUseProgram(m_shaderProgram->GetProgramID());

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        float vertices[] = {
            x,         y,          0.0f, 1.0f,
            1.0f,      1.0f,       0.0,  0.0,
            x + width, y,          0.0f, 1.0f,
            1.0f,      1.0f,       1.0,  0.0,
            x + width, y + height, 0.0f, 1.0f,
            1.0f,      1.0f,       1.0,  1.0,
            x,         y + height, 0.0f, 1.0f,
            1.0f,      1.0f,       0.0,  1.0};

        unsigned int indices[] = {0, 1, 2, 3};

        auto verticesCount{4};

        auto indicesCount{4};

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto needCreateBuffers{false};

        if (useOperationsMemory &&
            m_operationsMemory.contains(x) &&
            m_operationsMemory.at(x).contains(y) &&
            m_operationsMemory.at(x).at(y).contains(
                textureID))
        {
            needCreateBuffers = false;
        }
        else
        {
            needCreateBuffers = true;

            glGenVertexArrays(1, &vao);

            glGenBuffers(1, &vbo);

            glGenBuffers(1, &ibo);
        }

        auto needFillBuffers{false};

        if (!needCreateBuffers)
        {
            auto &entry = m_operationsMemory.at(x).at(y).at(
                textureID);

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            if (x != entry.x || y != entry.y ||
                width != entry.width ||
                height != entry.height)
            {
                needFillBuffers = true;

                entry.x = x;

                entry.y = y;

                entry.width = width;

                entry.height = height;
            }
        }
        else
        {
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            Image2DRenderingOperation entry;

            entry.vao = vao;

            entry.ibo = ibo;

            entry.vbo = vbo;

            entry.x = x;

            entry.y = y;

            entry.width = width;

            entry.height = height;

            m_operationsMemory[x][y][textureID] = entry;

            needFillBuffers = true;
        }

        if (needFillBuffers)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(indices[0]) * indicesCount,
                         indices, GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(vertices[0]) * 8 *
                             verticesCount,
                         vertices, GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(vertices[0]) * 8,
                                  0);

            glEnableVertexAttribArray(0);

            glVertexAttribPointer(
                1, 3, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 8,
                (void *)(sizeof(vertices[0]) * 3));

            glEnableVertexAttribArray(1);

            glVertexAttribPointer(
                2, 2, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 8,
                (void *)(sizeof(vertices[0]) * 6));

            glEnableVertexAttribArray(2);
        }

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT,
                       nullptr);

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

        DrawImage(hash, x, y, width, height);
    }

    void Image2DRenderer::DrawImage(StringView imageName,
                                    float x, float y,
                                    float width,
                                    float height)
    {
        this->DrawImage(Hash(imageName), x, y, width,
                        height);
    }
}