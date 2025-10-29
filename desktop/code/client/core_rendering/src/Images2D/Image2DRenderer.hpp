//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "RendererBase.hpp"

#include "Image2DRenderingOperation.hpp"

namespace Forradia
{
    class Image2DRenderer : public RendererBase
    {
      public:
        ~Image2DRenderer()
        {
            this->Cleanup();
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

      protected:
        String GetVSSource() const override;

        String GetFSSource() const override;

      private:
        void Cleanup();

        std::map<
            float,
            std::map<float,
                     std::map<GLuint,
                              Image2DRenderingOperation>>>
            m_operationsMemory;
    };
}