//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class RenderersCollection
    {
      public:
        class ShaderProgram
        {
          public:
            ShaderProgram(StringView vertexShaderSource,
                          StringView fragmentShaderSource)
            {
                Initialize(vertexShaderSource,
                           fragmentShaderSource);
            }

            ~ShaderProgram()
            {
                Cleanup();
            }

            auto GetProgramID() const
            {
                return m_programID;
            }

          private:
            void
            Initialize(StringView vertexShaderSource,
                       StringView fragmentShaderSource);

            void Cleanup();

            GLuint m_programID;
        };

        class Image2DRenderer
        {
          public:
            Image2DRenderer()
            {
                Initialize();
            };

            ~Image2DRenderer()
            {
                Cleanup();
            }

            void DrawImage(StringView imageName, float x,
                           float y, float width,
                           float height);

            void DrawImage(int imageNameHash, float x,
                           float y, float width,
                           float height);

            void
            DrawTexture(GLuint textureID, float x, float y,
                        float width, float height,
                        bool useOperationsMemory = false);

            void DrawImageAutoHeight(StringView imageName,
                                     float x, float y,
                                     float width);

          private:
            void Initialize();

            void Cleanup();

            class Image2DRenderingOperation
            {
              public:
                float x;

                float y;

                float width;

                float height;

                GLuint vao;

                GLuint ibo;

                GLuint vbo;
            };

            SharedPtr<ShaderProgram> m_shaderProgram;
            std::map<
                float,
                std::map<
                    float,
                    std::map<GLuint,
                             Image2DRenderingOperation>>>
                m_operationsMemory;
        };

        class GroundRenderer
        {
          public:
            GroundRenderer()
            {
                Initialize();
            };

            ~GroundRenderer()
            {
                Cleanup();
            }

            void DrawTile(int imageNameHash,
                          int xCoordinate, int yCoordinate,
                          float tileSize,
                          Point3F cameraPosition,
                          Vector<float> &elevations,
                          float elevationHeight);

            void DrawTexture(GLuint textureID,
                             Vector<float> &vertices,
                             Point3F cameraPosition);

          private:
            void Initialize();

            void Cleanup();

            class GroundRenderingOperation
            {
              public:
                float x;

                float y;

                GLuint vao;

                GLuint ibo;

                GLuint vbo;
            };

            glm::vec3 ComputeNormal(glm::vec3 p1,
                                    glm::vec3 p2,
                                    glm::vec3 p3);

            SharedPtr<ShaderProgram> m_shaderProgram;

            std::map<
                float,
                std::map<
                    float,
                    std::map<GLuint,
                             GroundRenderingOperation>>>
                m_operationsMemory;
        };

        class ModelRenderer
        {
          public:
            ModelRenderer()
            {
                Initialize();
            }

            ~ModelRenderer()
            {
                Cleanup();
            }

            void DrawModel(int modelNameHash, float x,
                           float y, float elevations,
                           Point3F cameraPosition,
                           float elevationHeight);

          private:
            void Initialize();

            void Cleanup();

            class ModelRenderingOperation
            {
              public:
                float x;

                float y;

                float z;

                int verticesCount;

                GLuint vao;

                GLuint ibo;

                GLuint vbo;
            };

            SharedPtr<ShaderProgram> m_shaderProgram;

            std::map<
                float,
                std::map<
                    float,
                    std::map<
                        float,
                        std::map<int,
                                 ModelRenderingOperation>>>>
                m_operationsMemory;

            static constexpr float k_modelScale{0.25f};
        };

        enum struct FontSizes
        {
            _20 = 20,
            _26 = 26
        };

        class TextRenderer
        {
          public:
            TextRenderer()
            {
                Initialize();
            }

            void
            DrawString(StringView text, float x, float y,
                       FontSizes fontSizes = FontSizes::_20,
                       bool centerAlign = false,
                       Color textColor =
                           Colors::WheatTransparent) const;

          private:
            void Initialize();

            void AddFonts();

            const String k_defaultFontPath{
                "./Resources/fonts/PixeloidSans.ttf"};

            std::map<FontSizes, SharedPtr<TTF_Font>>
                m_fonts;
        };
    };
}