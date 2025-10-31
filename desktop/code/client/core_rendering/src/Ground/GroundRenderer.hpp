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
                      const Vector<float> &elevations,
                      float elevationHeight);

      protected:
        String GetVSSource() const override;

        String GetFSSource() const override;

      private:
        void Cleanup();

        Vector<float> CalcTileVerticesNoNormals(
            int xCoordinate, int yCoordinate,
            float tileSize, const Vector<float> &elevations,
            float elevationHeight);

        Vector<float> CalcTileVerticesWithNormals(
            const Vector<float> &verticesNoNormals);

        Vector<glm::vec3> CalcTileNormals(
            const Vector<float> &verticesNoNormals);

        std::map<
            int,
            std::map<
                int,
                std::map<GLuint, GroundRenderingOperation>>>
            m_operationsMemory;
    };
}