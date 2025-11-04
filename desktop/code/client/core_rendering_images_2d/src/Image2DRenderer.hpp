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

        void DrawImageByName(StringView imageName, float x,
                             float y, float width,
                             float height);

        void
        DrawImageByHash(int imageNameHash, float x, float y,
                        float width, float height,
                        bool useOperationsCache = true);

        void DrawImageByTextureID(
            GLuint textureID, float x, float y, float width,
            float height, bool useOperationsCache = true);

        void DrawImageAutoHeight(StringView imageName,
                                 float x, float y,
                                 float width);

      protected:
        String GetVSSource() const override;

        String GetFSSource() const override;

        void SetupAttributeLayout() const override;

      private:
        void Cleanup();

        void SetupState() const;

        void ResetState() const;

        bool
        DrawingOperationIsCached(float x, float y,
                                 GLuint textureID) const;

        std::map<
            float,
            std::map<float,
                     std::map<GLuint,
                              Image2DRenderingOperation>>>
            m_operationsCache;
    };
}