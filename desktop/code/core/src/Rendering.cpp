//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Rendering.hpp"
#include "Assets/Images/ImageBank.hpp"
#include "Core.hpp"
#include "SDLDevice.hpp"
#include "Theme0Properties.hpp"

namespace Forradia
{
    void RenderersCollection::ShaderProgram::Initialize(
        StringView vertexShaderSource,
        StringView fragmentShaderSource)
    {
        GLuint vertexShader{
            glCreateShader(GL_VERTEX_SHADER)};

        const GLchar *source{
            (const GLchar *)vertexShaderSource.data()};

        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled{0};

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS,
                      &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength{0};

            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH,
                          &maxLength);

            Vector<GLchar> infoLog(maxLength);

            glGetShaderInfoLog(vertexShader, maxLength,
                               &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);

            return;
        }

        GLuint fragmentShader{
            glCreateShader(GL_FRAGMENT_SHADER)};

        source =
            (const GLchar *)fragmentShaderSource.data();

        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,
                      &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength{0};

            glGetShaderiv(fragmentShader,
                          GL_INFO_LOG_LENGTH, &maxLength);

            Vector<GLchar> infoLog(maxLength);

            glGetShaderInfoLog(fragmentShader, maxLength,
                               &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);

            glDeleteShader(vertexShader);

            return;
        }

        m_programID = glCreateProgram();

        glAttachShader(m_programID, vertexShader);

        glAttachShader(m_programID, fragmentShader);

        glLinkProgram(m_programID);

        GLint isLinked{0};

        glGetProgramiv(m_programID, GL_LINK_STATUS,
                       (int *)&isLinked);

        if (isLinked == GL_FALSE)
        {
            GLint maxLength{0};

            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH,
                           &maxLength);

            Vector<GLchar> infoLog(maxLength);

            glGetProgramInfoLog(m_programID, maxLength,
                                &maxLength, &infoLog[0]);

            glDeleteProgram(m_programID);

            glDeleteShader(vertexShader);

            glDeleteShader(fragmentShader);

            return;
        }

        glDetachShader(m_programID, vertexShader);

        glDetachShader(m_programID, fragmentShader);

        glDeleteShader(vertexShader);

        glDeleteShader(fragmentShader);
    }

    void RenderersCollection::ShaderProgram::Cleanup()
    {
        glDeleteProgram(m_programID);
    }

    void RenderersCollection::Image2DRenderer::Initialize()
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

    void RenderersCollection::Image2DRenderer::Cleanup()
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

    void RenderersCollection::Image2DRenderer::DrawImage(
        int imageNameHash, float x, float y, float width,
        float height)
    {
        auto textureID{
            _<ImageBank>().GetTexture(imageNameHash)};

        Image2DRenderer::DrawTexture(textureID, x, y, width,
                                     height, true);
    }

    void RenderersCollection::Image2DRenderer::DrawTexture(
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

    void RenderersCollection::Image2DRenderer::
        DrawImageAutoHeight(StringView imageName, float x,
                            float y, float width)
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

    void RenderersCollection::Image2DRenderer::DrawImage(
        StringView imageName, float x, float y, float width,
        float height)
    {
        this->DrawImage(Hash(imageName), x, y, width,
                        height);
    }

    void RenderersCollection::GroundRenderer::Initialize()
    {
        String vertexShaderSource{R"(
      #version 330 core
      layout (location = 0) in vec3 aPos;
      layout (location = 1) in vec3 aColor;
      layout (location = 2) in vec2 aTexCoord;
      layout (location = 3) in vec3 aNormal;

      uniform mat4 MVP;

      out vec3 ourColor;
      out vec2 TexCoord;
      out vec3 Normal;

      void main()
      {
          vec4 v = vec4(aPos, 1.0);
          gl_Position = MVP * v;
          gl_Position.y = gl_Position.y * -1.0;
          ourColor = aColor;
          TexCoord = aTexCoord;
          Normal = aNormal;
      }
    )"};

        String fragmentShaderSource{R"(
      #version 330 core
      out vec4 FragColor;
        
      in vec3 ourColor;
      in vec2 TexCoord;
      in vec3 Normal;

      uniform sampler2D ourTexture;


      void main()
      {
          vec3 lightColor = vec3(1.0, 1.0, 0.8);
          vec3 norm = normalize(Normal);
          vec3 lightDir = vec3(10.0, 10.0, 20.0);
          float diff = max(dot(norm, lightDir), 0.0);
          vec3 diffuse = diff * lightColor*0.05;
          vec4 objectColor = texture(ourTexture, TexCoord);
          vec3 result = diffuse* objectColor.rgb;
          FragColor = vec4(result, objectColor.a);
      }
    )"};

        m_shaderProgram = std::make_shared<ShaderProgram>(
            vertexShaderSource, fragmentShaderSource);
    }

    void RenderersCollection::GroundRenderer::Cleanup()
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

    void RenderersCollection::GroundRenderer::DrawTile(
        int imageNameHash, int xCoordinate, int yCoordinate,
        float tileSize, Point3F cameraPosition,
        Vector<float> &elevations, float elevationHeight)
    {
        auto textureID{
            _<ImageBank>().GetTexture(imageNameHash)};

        auto x{tileSize * (xCoordinate)};

        auto y{tileSize * (yCoordinate)};

        auto width{tileSize};

        auto height{tileSize};

        Vector<float> vertices{
            {x,
             y,
             elevations.at(0) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             0.0,
             0.0,
             x + width,
             y,
             elevations.at(1) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             0.0,
             x + width + width,
             y,
             elevations.at(2) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x,
             y + height,
             elevations.at(3) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             0.0,
             1.0,
             x + width,
             y + height,
             elevations.at(4) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x + width + width,
             y + height,
             elevations.at(5) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x,
             y + height + height,
             elevations.at(6) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x + width,
             y + height + height,
             elevations.at(7) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0,
             x + width + width,
             y + height + height,
             elevations.at(8) * elevationHeight,
             1.0f,
             1.0f,
             1.0f,
             1.0,
             1.0}};

        GroundRenderer::DrawTexture(textureID, vertices,
                                    cameraPosition);
    }

    void RenderersCollection::GroundRenderer::DrawTexture(
        GLuint textureID, Vector<float> &verticesVec,
        Point3F cameraPosition)
    {
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_FRONT);

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width,
                   canvasSize.height);

        glUseProgram(m_shaderProgram->GetProgramID());

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        auto verticesNoNormals = verticesVec.data();

        unsigned int indices[] = {0, 1, 2, 3};

        Vector<glm::vec3> normals;

        auto verticesCount{4};

        auto indicesCount{4};

        auto _00x{verticesNoNormals[0 * 8 + 0]};
        auto _00y{verticesNoNormals[0 * 8 + 1]};
        auto _00z{verticesNoNormals[0 * 8 + 2]};
        auto _10x{verticesNoNormals[1 * 8 + 0]};
        auto _10y{verticesNoNormals[1 * 8 + 1]};
        auto _10z{verticesNoNormals[1 * 8 + 2]};
        auto _20x{verticesNoNormals[2 * 8 + 0]};
        auto _20y{verticesNoNormals[2 * 8 + 1]};
        auto _20z{verticesNoNormals[2 * 8 + 2]};
        auto _01x{verticesNoNormals[3 * 8 + 0]};
        auto _01y{verticesNoNormals[3 * 8 + 1]};
        auto _01z{verticesNoNormals[3 * 8 + 2]};
        auto _11x{verticesNoNormals[4 * 8 + 0]};
        auto _11y{verticesNoNormals[4 * 8 + 1]};
        auto _11z{verticesNoNormals[4 * 8 + 2]};
        auto _21x{verticesNoNormals[5 * 8 + 0]};
        auto _21y{verticesNoNormals[5 * 8 + 1]};
        auto _21z{verticesNoNormals[5 * 8 + 2]};
        auto _02x{verticesNoNormals[6 * 8 + 0]};
        auto _02y{verticesNoNormals[6 * 8 + 1]};
        auto _02z{verticesNoNormals[6 * 8 + 2]};
        auto _12x{verticesNoNormals[7 * 8 + 0]};
        auto _12y{verticesNoNormals[7 * 8 + 1]};
        auto _12z{verticesNoNormals[7 * 8 + 2]};
        auto _22x{verticesNoNormals[8 * 8 + 0]};
        auto _22y{verticesNoNormals[8 * 8 + 1]};
        auto _22z{verticesNoNormals[8 * 8 + 2]};

        glm::vec3 v00 = {_00x, _00y, _00z};
        glm::vec3 v10 = {_10x, _10y, _10z};
        glm::vec3 v20 = {_20x, _20y, _20z};
        glm::vec3 v01 = {_01x, _01y, _01z};
        glm::vec3 v11 = {_11x, _11y, _11z};
        glm::vec3 v21 = {_21x, _21y, _21z};
        glm::vec3 v02 = {_02x, _02y, _02z};
        glm::vec3 v12 = {_12x, _12y, _12z};
        glm::vec3 v22 = {_22x, _22y, _22z};

        glm::vec3 normal00 =
            this->ComputeNormal(v10, v00, v01);
        glm::vec3 normal10 =
            this->ComputeNormal(v20, v10, v11);
        glm::vec3 normal11 =
            this->ComputeNormal(v21, v11, v12);
        glm::vec3 normal01 =
            this->ComputeNormal(v11, v01, v02);

        normal00.z *= -1.0f;
        normal10.z *= -1.0f;
        normal11.z *= -1.0f;
        normal01.z *= -1.0f;

        normals.push_back(normal00);
        normals.push_back(normal10);
        normals.push_back(normal11);
        normals.push_back(normal01);

        Vector<float> verticesVector;

        auto fn{
            [&](int i, int j)
            {
                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 0]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 1]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 2]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 3]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 4]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 5]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 6]);

                verticesVector.push_back(
                    verticesNoNormals[i * 8 + 7]);

                verticesVector.push_back(normals.at(j).x);

                verticesVector.push_back(normals.at(j).y);

                verticesVector.push_back(normals.at(j).z);
            }};

        fn(0, 0);

        fn(1, 1);

        fn(4, 2);

        fn(3, 3);

        auto vertices{verticesVector.data()};

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto needCreateBuffers{false};

        if (m_operationsMemory.contains(
                verticesVec.at(0)) &&
            m_operationsMemory.at(verticesVec.at(0))
                .contains(verticesVec.at(1)) &&
            m_operationsMemory.at(verticesVec.at(0))
                .at(verticesVec.at(1))
                .contains(textureID))
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
            auto &entry =
                m_operationsMemory.at(verticesVec.at(0))
                    .at(verticesVec.at(1))
                    .at(textureID);

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            if (verticesVec.at(0) != entry.x ||
                verticesVec.at(1) != entry.y)
            {
                needFillBuffers = true;

                entry.x = verticesVec.at(0);

                entry.y = verticesVec.at(1);
            }
        }
        else
        {
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            GroundRenderingOperation entry;

            entry.vao = vao;

            entry.ibo = ibo;

            entry.vbo = vbo;

            entry.x = verticesVec.at(0);

            entry.y = verticesVec.at(1);

            m_operationsMemory[verticesVec.at(
                0)][verticesVec.at(1)][textureID] = entry;

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
                         sizeof(vertices[0]) * 11 *
                             verticesCount,
                         vertices, GL_DYNAMIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(vertices[0]) * 11,
                                  0);

            glEnableVertexAttribArray(0);

            glVertexAttribPointer(
                1, 3, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 11,
                (void *)(sizeof(vertices[0]) * 3));

            glEnableVertexAttribArray(1);

            glVertexAttribPointer(
                2, 2, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 11,
                (void *)(sizeof(vertices[0]) * 6));

            glEnableVertexAttribArray(2);

            glVertexAttribPointer(
                3, 3, GL_FLOAT, GL_FALSE,
                sizeof(vertices[0]) * 11,
                (void *)(sizeof(vertices[0]) * 8));

            glEnableVertexAttribArray(3);
        }

        glm::mat4 modelMatrix = glm::mat4(1.0f);

        // auto tileSize{0.5f};

        // modelMatrix = glm::translate(
        //     modelMatrix,
        //     glm::vec3(0.5f/2, 0.5f/2, 0.0f));

        //  lookAt function takes camera position, camera
        //  target and up vector.
        glm::mat4 cameraMatrix = glm::lookAt(
            glm::vec3(cameraPosition.x,
                      cameraPosition.y - 2.0f,
                      -cameraPosition.z + 2.5f),
            glm::vec3(cameraPosition.x, cameraPosition.y,
                      -cameraPosition.z),
            glm::vec3(0.0f, 0.0f, -1.0f));

        auto aspectRatio{
            CalcAspectRatio(_<SDLDevice>().GetWindow())};

        // perspective function takes field of view, aspect
        // ratio, near clipping distance and far clipping
        // distance.
        glm::mat4 projectionMatrix = glm::perspective(
            90.0f, aspectRatio, 0.1f, 100.0f);

        glm::mat4 finalMatrix =
            projectionMatrix * cameraMatrix * modelMatrix;

        GLuint mvpMatrixID = glGetUniformLocation(
            m_shaderProgram->GetProgramID(), "MVP");

        glUniformMatrix4fv(mvpMatrixID, 1, GL_FALSE,
                           &finalMatrix[0][0]);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT,
                       nullptr);

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisable(GL_DEPTH_TEST);
    }

    glm::vec3
    RenderersCollection::GroundRenderer::ComputeNormal(
        glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
    {
        // Uses p2 as a new origin for p1, p3.

        auto a = p3 - p2;

        auto b = p1 - p2;

        // Compute the cross product a X b to get the face
        // normal.

        return glm::normalize(glm::cross(a, b));
    }

    void RenderersCollection::ModelRenderer::Initialize()
    {
        String vertexShaderSource{R"(
      #version 330 core
      layout (location = 0) in vec3 aPos;
      layout (location = 1) in vec3 aNormal;
      layout (location = 2) in vec2 aTexCoord;

      out vec3 FragPos;
      out vec3 Normal;
      out vec2 TexCoord;

      uniform mat4 projection; 
      uniform mat4 view; 
      uniform mat4 model;

      uniform float scale;

      void main()
      {
          FragPos = vec3(model * vec4(aPos, 1.0));
          Normal = vec3(model * vec4(aNormal, 0.0));
          gl_Position = projection * view * vec4(FragPos, 1.0);
          gl_Position.y = gl_Position.y * -1.0;
          TexCoord = aTexCoord;
      }
    )"};

        String fragmentShaderSource{R"(
      #version 330 core
      out vec4 FragColor;

      in vec3 Normal;  
      in vec3 FragPos;
      in vec2 TexCoord;

      uniform vec3 lightPos;
      uniform vec3 viewPos;
      uniform sampler2D ourTexture;

      vec3 lightColor = vec3(1,1,1);
      //vec3 objectColor = vec3(0.6, 0.6, 0.6);
      uniform float shininess = 32.0f;
      uniform vec3 material_specular = vec3(0.1f, 0.1f, 0.1f);
      uniform vec3 light_specular = vec3(0.5f, 0.5f, 0.5f);

      void main()
      {
          // ambient
          float ambientStrength = 0.2;
          vec3 ambient = ambientStrength * lightColor;

          // diffuse 
          vec3 norm = normalize(Normal);
          vec3 lightDir = normalize(lightPos - FragPos);
          float diff = max(dot(norm, lightDir), 0.0);
          vec3 diffuse = diff * lightColor;

          // specular
          vec3 viewDir = normalize(viewPos - FragPos);
          vec3 reflectDir = reflect(-lightDir, norm);  
          float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
          vec3 specular = light_specular * (spec * material_specular);  

          vec4 objectColor = texture(ourTexture, TexCoord);

          vec3 result = (ambient + diffuse + specular) * objectColor.rgb;
          FragColor = vec4(result, 1.0);
      }
    )"};

        m_shaderProgram = std::make_shared<ShaderProgram>(
            vertexShaderSource, fragmentShaderSource);
    }

    void RenderersCollection::ModelRenderer::Cleanup()
    {
        for (auto &entry : m_operationsMemory)
        {
            for (auto &entry2 : entry.second)
            {
                for (auto &entry3 : entry2.second)
                {
                    for (auto &entry4 : entry3.second)
                    {
                        glDeleteVertexArrays(
                            1, &entry4.second.vao);

                        glDeleteBuffers(1,
                                        &entry4.second.ibo);

                        glDeleteBuffers(1,
                                        &entry4.second.vbo);
                    }
                }
            }
        }

        glUseProgram(0);
    }

    void RenderersCollection::ModelRenderer::DrawModel(
        int modelNameHash, float x, float y,
        float elevation, Point3F cameraPosition,
        float elevationHeight)
    {
        x += _<Theme0::Theme0Properties>().k_tileSize * 4.0f / 2.0f;

        y += _<Theme0::Theme0Properties>().k_tileSize * 4.0f / 2.0f;

        glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);

        glCullFace(GL_FRONT);

        auto model{
            _<Engine::Assets::Models::ModelBank>().GetModel(
                modelNameHash)};

        auto &meshes{model->GetMeshesRef()};

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        glViewport(0, 0, canvasSize.width,
                   canvasSize.height);

        glUseProgram(m_shaderProgram->GetProgramID());

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA,
                            GL_ONE_MINUS_DST_ALPHA, GL_ONE);

        GLuint vao;
        GLuint ibo;
        GLuint vbo;

        auto needCreateBuffers{false};

        if (m_operationsMemory.contains(x) &&
            m_operationsMemory.at(x).contains(y) &&
            m_operationsMemory.at(x).at(y).contains(
                elevation) &&
            m_operationsMemory.at(x)
                .at(y)
                .at(elevation)
                .contains(modelNameHash))
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
            auto &entry = m_operationsMemory.at(x)
                              .at(y)
                              .at(elevation)
                              .at(modelNameHash);

            vao = entry.vao;

            ibo = entry.ibo;

            vbo = entry.vbo;

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            if (x != entry.x || y != entry.y ||
                elevation != entry.z)
            {
                needFillBuffers = true;

                entry.x = x;

                entry.y = y;

                entry.z = elevation;
            }
        }
        else
        {
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            ModelRenderingOperation entry;

            entry.vao = vao;

            entry.ibo = ibo;

            entry.vbo = vbo;

            entry.x = x;

            entry.y = y;

            entry.z = elevation;

            m_operationsMemory[x][y][elevation]
                              [modelNameHash] = entry;

            needFillBuffers = true;
        }
        if (needFillBuffers)
        {

            Vector<unsigned int> indicesVector;

            Vector<glm::vec3> normals;

            Vector<float> verticesVector;

            auto i{0};

            for (auto &mesh : meshes)
            {
                for (auto &vertex : mesh.vertices)
                {
                    verticesVector.push_back(
                        x +
                        vertex.position.x * k_modelScale);

                    verticesVector.push_back(
                        y +
                        vertex.position.y * k_modelScale);

                    verticesVector.push_back(
                        elevation * elevationHeight +
                        vertex.position.z * k_modelScale);

                    verticesVector.push_back(
                        vertex.normal.x);

                    verticesVector.push_back(
                        vertex.normal.y);

                    verticesVector.push_back(
                        vertex.normal.z);

                    verticesVector.push_back(vertex.uv.x);

                    verticesVector.push_back(vertex.uv.y);
                }

                for (auto &index : mesh.indices)
                {
                    indicesVector.push_back(
                        i + mesh.indices[index]);
                }

                i += mesh.vertices.size();
            }

            auto verticesCount{verticesVector.size() / 8};

            auto indicesCount{indicesVector.size()};

            auto vertices{verticesVector.data()};

            auto indices{indicesVector.data()};

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(indices[0]) * indicesCount,
                         indices, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(vertices[0]) * 8 *
                             verticesCount,
                         vertices, GL_STATIC_DRAW);

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

            auto &entry = m_operationsMemory.at(x)
                              .at(y)
                              .at(elevation)
                              .at(modelNameHash);

            entry.verticesCount = verticesCount;
        }

        auto &entry =
            m_operationsMemory.at(x).at(y).at(elevation).at(
                modelNameHash);

        glm::mat4 modelMatrix = glm::mat4(1.0f);

        // lookAt function takes camera position, camera
        // target and up vector.

        glm::mat4 cameraMatrix = glm::lookAt(
            glm::vec3(cameraPosition.x,
                      cameraPosition.y - 2.0f,
                      -cameraPosition.z + 2.5f),
            glm::vec3(cameraPosition.x, cameraPosition.y,
                      -cameraPosition.z),
            glm::vec3(0.0f, 0.0f, -1.0f));

        auto aspectRatio{
            CalcAspectRatio(_<SDLDevice>().GetWindow())};

        // perspective function takes field of view, aspect
        // ratio, near clipping distance and far clipping
        // distance.

        glm::mat4 projectionMatrix = glm::perspective(
            90.0f, aspectRatio, 0.1f, 100.0f);

        GLuint matrixProjection = glGetUniformLocation(
            m_shaderProgram->GetProgramID(), "projection");
        glUniformMatrix4fv(matrixProjection, 1, GL_FALSE,
                           &projectionMatrix[0][0]);

        GLuint matrixModel = glGetUniformLocation(
            m_shaderProgram->GetProgramID(), "model");
        glUniformMatrix4fv(matrixModel, 1, GL_FALSE,
                           &modelMatrix[0][0]);

        GLuint matrixView = glGetUniformLocation(
            m_shaderProgram->GetProgramID(), "view");

        glUniformMatrix4fv(matrixView, 1, GL_FALSE,
                           &cameraMatrix[0][0]);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        auto textureName{meshes.at(0).textures.at(0).path};

        auto textureNameHash{Hash(textureName)};

        auto textureID{
            _<ImageBank>().GetTexture(textureNameHash)};

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawElements(GL_TRIANGLES, entry.verticesCount,
                       GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisable(GL_DEPTH_TEST);
    }

    void RenderersCollection::TextRenderer::Initialize()
    {
        TTF_Init();

        this->AddFonts();
    }

    void RenderersCollection::TextRenderer::AddFonts()
    {
        auto absFontPath{String(SDL_GetBasePath()) +
                         k_defaultFontPath.data()};

        for (auto fontSize :
             {FontSizes::_20, FontSizes::_26})
        {
            auto fontPathUnixStyle{
                Replace(absFontPath, '\\', '/')};

            auto fontSizeN{CInt(fontSize)};

            auto newFont{SharedPtr<TTF_Font>(
                TTF_OpenFont(fontPathUnixStyle.c_str(),
                             fontSizeN),
                SDLDeleter())};

            if (!newFont)
            {
                PrintLine("Error loading font.");

                return;
            }

            m_fonts.insert({fontSize, newFont});
        }
    }

    void RenderersCollection::TextRenderer::DrawString(
        StringView text, float x, float y,
        FontSizes fontSize, bool centerAlign,
        Color textColor) const
    {
        if (text.empty())
        {
            return;
        }

        auto fontRaw{m_fonts.at(fontSize).get()};

        Size textureDimensions;

        TTF_SizeText(fontRaw, text.data(),
                     &textureDimensions.width,
                     &textureDimensions.height);

        SDL_Rect destination;

        auto canvasSize{
            GetCanvasSize(_<SDLDevice>().GetWindow())};

        destination.x = CInt(x * canvasSize.width);

        destination.y = CInt(y * canvasSize.height);

        destination.w = textureDimensions.width;

        destination.h = textureDimensions.height;

        if (centerAlign)
        {
            destination.x -= destination.w / 2;

            destination.y -= destination.h / 2;
        }

        auto textHash{Hash(text)};

        auto xx{CFloat(CInt(x * 1000))};

        auto yy{CFloat(CInt(y * 1000))};

        auto textureAlreadyExists{
            _<ImageBank>().TextTextureExists(xx, yy,
                                             textHash)};

        auto texture{_<ImageBank>().ObtainTextTexture(
            xx, yy, textHash)};

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glEnable(GL_TEXTURE_2D);

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, texture);

        if (!textureAlreadyExists)
        {
            auto sdlColor{textColor.ToSDLColor()};

            auto surface{TTF_RenderText_Solid(
                fontRaw, text.data(), sdlColor)};

            auto newWidth{surface->w};

            auto newHeight{surface->h};

            auto intermediary = SDL_CreateRGBSurface(
                0, newWidth, newHeight, 32, 0x000000ff,
                0x0000ff00, 0x00ff0000, 0xff000000);

            SDL_BlitSurface(surface, 0, intermediary, 0);

            glTexImage2D(GL_TEXTURE_2D, 0, 4,
                         intermediary->w, intermediary->h,
                         0, GL_RGBA, GL_UNSIGNED_BYTE,
                         intermediary->pixels);

            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MIN_FILTER,
                            GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,
                            GL_TEXTURE_MAG_FILTER,
                            GL_LINEAR);

            SDL_FreeSurface(intermediary);

            SDL_FreeSurface(surface);
        }

        auto xF{CFloat(destination.x) / canvasSize.width};

        auto yF{CFloat(destination.y) / canvasSize.height};

        auto widthF{CFloat(destination.w) /
                    canvasSize.width};

        auto heightF{CFloat(destination.h) /
                     canvasSize.height};

        _<Image2DRenderer>().DrawTexture(texture, xF, yF,
                                         widthF, heightF);
    }
}