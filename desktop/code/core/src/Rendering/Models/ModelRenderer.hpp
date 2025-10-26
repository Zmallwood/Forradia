//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    class ShaderProgram;

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

        void DrawModel(int modelNameHash, float x, float y,
                       float elevations,
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
}