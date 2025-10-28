//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Base/RendererBase.hpp"

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
                       Point3F cameraPosition,
                       float elevationHeight);

      protected:
        String GetVSSource() const override;

        String GetFSSource() const override;

      private:
        void Cleanup();

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