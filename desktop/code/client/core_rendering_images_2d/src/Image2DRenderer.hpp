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
    // TODO: Remove the useOperationsCache parameter from
    // all methods. Probably not needed anymore.
    class Image2DRenderer : public RendererBase
    {
      public:
        ~Image2DRenderer()
        {
            this->Cleanup();
        }

        void DrawImageByName(int uniqueRenderID,
                             StringView imageName, float x,
                             float y, float width,
                             float height,
                             bool updateExisting = false);

        void DrawImageByHash(int uniqueRenderID,
                             int imageNameHash, float x,
                             float y, float width,
                             float height,
                             bool updateExisting = false);

        void DrawImageByTextureID(
            int uniqueRenderID, GLuint textureID, float x,
            float y, float width, float height,
            bool updateExisting = false);

        void DrawImageAutoHeight(int uniqueRenderID,
                                 StringView imageName,
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
        DrawingOperationIsCached(int uniqueRenderID) const;

        std::map<int, Image2DRenderingOperation>
            m_operationsCache;
    };
}