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

        void DrawTexture(GLuint textureID,
                         Vector<float> &vertices,
                         Point3F cameraPosition);

      protected:
        String GetVSSource() const override;

        String GetFSSource() const override;

      private:
        void Cleanup();

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