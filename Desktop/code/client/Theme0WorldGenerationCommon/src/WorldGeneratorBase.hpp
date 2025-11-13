//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class WorldArea;

    class WorldGeneratorBase
    {
      public:
        void Prepare();

      protected:
        float GetDistance(int x1, int y1, int x2, int y2) const;

        int GetElevationAt(int x, int y) const;

        bool IsValidForWater(int x, int y) const;

        bool IsValidForTree(int x, int y) const;

        bool IsNearWater(int x, int y, int radius) const;

        bool IsAdjacentToWater(int x, int y) const;

        void CreateBiomeCluster(int centerX, int centerY, int radius, const char *groundType,
                                float density) const;

        void SetAdjacentTilesElevationToZero(int x, int y) const;

        int GetMaxElevation() const;

        int GetMaxSlopePerTile() const;

        int GetMaxAllowedElevation(int x, int y, int currentElevation) const;

        int ClampElevation(int elevation) const;

        void CreateElevationHill(int centerX, int centerY, int radius, int maxElevation) const;

        auto GetDefaultGroundElevation() const
        {
            return k_defaultGroundElevation;
        }

        auto GetWorldArea() const
        {
            return m_worldArea;
        }

        auto GetSize() const
        {
            return m_size;
        }

        auto GetScale() const
        {
            return m_scale;
        }

      private:
        const int k_defaultGroundElevation{10};

        SharedPtr<WorldArea> m_worldArea;

        Size m_size;

        float m_scale;
    };
}