//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Image2DRenderer.hpp"

#include "Rendering/ShaderProgram.hpp"

#include "Images/ImageBank.hpp"

#include "SDLDevice.hpp"

namespace Forradia
{
    void Image2DRenderer::Initialize()
    {
        String vertexShaderSource{R"(
      #version 330 core
      layout (location = 0) in vec3 aPos;
      layout (location = 1) in vec3 aColor;
      layout (location = 2) in vec2 aTexCoord;

      out vec3 ourColor;
      out vec2 TexCoord;

      void main()
      {
          gl_Position = vec4(aPos, 1.0);
          gl_Position.x = gl_Position.x * 2.0 - 1.0;
          gl_Position.y = gl_Position.y * -2.0 + 1.0;
          ourColor = aColor;
          TexCoord = aTexCoord;
      }
    )"};

        String fragmentShaderSource{R"(
      #version 330 core
      out vec4 FragColor;
        
      in vec3 ourColor;
      in vec2 TexCoord;

      uniform sampler2D ourTexture;

      void main()
      {
          FragColor = texture(ourTexture, TexCoord);
      }
    )"};

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
            _<ImageBank>().GetTexture(imageNameHash)};

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

            Image2DRenderer::Image2DRenderingOperation
                entry;

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

        auto imageSize{_<ImageBank>().GetImageSize(hash)};

        if (imageSize.width <= 0 || imageSize.height <= 0)
        {
            return;
        }

        auto canvasAspectRatio{
            CalcAspectRatio(_<SDLDevice>().GetWindow())};

        auto imageAspectRatio{CFloat(imageSize.width) /
                              imageSize.height};

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