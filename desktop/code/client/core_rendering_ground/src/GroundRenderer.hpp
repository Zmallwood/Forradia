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

        void DrawTile(int uniqueRenderID, int imageNameHash,
                      int xCoordinate, int yCoordinate,
                      float tileSize,
                      const Vector<float> &elevations,
                      float elevationHeight,
                      bool forceUpdate = false);

        void Reset();

      protected:
        String GetVSSource() const override;

        String GetFSSource() const override;

        void SetupAttributeLayout() const override;

      private:
        void Cleanup();

        void SetupState() const;

        void RestoreState() const;

        bool
        DrawingOperationIsCached(int uniqueRenderID) const;

        Vector<float> CalcTileVerticesNoNormals(
            int xCoordinate, int yCoordinate,
            float tileSize, const Vector<float> &elevations,
            float elevationHeight);

        Vector<float> CalcTileVerticesWithNormals(
            const Vector<float> &verticesNoNormals);

        Vector<glm::vec3> CalcTileNormals(
            const Vector<float> &verticesNoNormals);

        static constexpr unsigned short k_indices[] = {
            0, 1, 2, 3};

        std::map<int, GroundRenderingOperation>
            m_operationsCache;
    };
}