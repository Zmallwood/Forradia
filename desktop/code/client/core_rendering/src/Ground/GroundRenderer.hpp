//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "RendererBase.hpp"

#include "GroundRenderingOperation.hpp"

namespace Forradia
{
    class GroundRenderer : public RendererBase
    {
      public:
        ~GroundRenderer()
        {
            this->Cleanup();
        }

        void DrawTile(int imageNameHash, int xCoordinate,
                      int yCoordinate, float tileSize,
                      Point3F cameraPosition,
                      Vector<float> &elevations,
                      float elevationHeight);

      protected:
        void DoRendering(int imageNameHash, int xCoordinate,
                         int yCoordinate, float tileSize,
                         Point3F cameraPosition,
                         const Vector<float> &elevations,
                         float elevationHeight);

        String GetVSSource() const override;

        String GetFSSource() const override;

      private:
        void Cleanup();

        Vector<float>
        GetTileVertices(int xCoordinate, int yCoordinate,
                        float tileSize,
                        const Vector<float> &elevations,
                        float elevationHeight);

        glm::vec3 ComputeNormal(glm::vec3 p1, glm::vec3 p2,
                                glm::vec3 p3);

        std::map<
            float,
            std::map<
                float,
                std::map<GLuint, GroundRenderingOperation>>>
            m_operationsMemory;
    };
}