//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "RendererBase.hpp"

#include "ModelRenderingOperation.hpp"

namespace Forradia
{
    class ModelRenderer : public RendererBase
    {
      public:
        ~ModelRenderer()
        {
            this->Cleanup();
        }

        void DrawModel(int modelNameHash, float x, float y,
                       float elevations,
                       float elevationHeight);

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
                                 float elevation,
                                 int modelNameHash) const;

        std::map<
            float,
            std::map<
                float,
                std::map<
                    float,
                    std::map<int,
                             ModelRenderingOperation>>>>
            m_operationsCache;

        static constexpr float k_modelScale{0.25f};
    };
}