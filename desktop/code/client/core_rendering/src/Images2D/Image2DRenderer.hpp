//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Image2DRenderingOperation.hpp"

namespace Forradia
{
    class ShaderProgram;

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
                       float y, float width, float height);

        void DrawImage(int imageNameHash, float x, float y,
                       float width, float height);

        void DrawTexture(GLuint textureID, float x, float y,
                         float width, float height,
                         bool useOperationsMemory = false);

        void DrawImageAutoHeight(StringView imageName,
                                 float x, float y,
                                 float width);

      private:
        void Initialize();

        void Cleanup();

        String GetVertexShaderSource() const;

        String GetFragmentShaderSource() const;

        SharedPtr<ShaderProgram> m_shaderProgram;
        std::map<
            float,
            std::map<float,
                     std::map<GLuint,
                              Image2DRenderingOperation>>>
            m_operationsMemory;
    };
}