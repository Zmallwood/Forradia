//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class WorldArea;

    class WorldGenerator
    {
      public:
        void GenerateNewWorld();

      private:
        void Prepare();

        void ClearWithDirt() const;

        // New creative generation methods
        void GenerateBiomeBasedTerrain() const;

        void GenerateElevationWithBiomes() const;

        void GenerateMountainRanges() const;

        void GenerateValleys() const;

        void GenerateNaturalRivers() const;

        void GenerateRiverFromSource(int startX, int startY, int length) const;

        void GenerateLakesInValleys() const;

        void EnforceMinimumElevationForNonWaterTiles() const;

        void GenerateGrassBiomes() const;

        void GenerateRockFormations() const;

        void GenerateForests() const;

        void GenerateMeadows() const;

        void GenerateObjectsInBiomes() const;

        void GenerateCreaturesInEcosystems() const;

        void GenerateRobotsInAreas() const;

        // Helper methods
        float GetDistance(int x1, int y1, int x2, int y2) const;

        int GetElevationAt(int x, int y) const;

        bool IsValidForWater(int x, int y) const;

        bool IsValidForTree(int x, int y) const;

        bool IsNearWater(int x, int y, int radius) const;

        bool IsAdjacentToWater(int x, int y) const;

        void CreateBiomeCluster(int centerX, int centerY, int radius, const char* groundType, float density) const;

        void CreateElevationHill(int centerX, int centerY, int radius, int maxElevation) const;

        void SetAdjacentTilesElevationToZero(int x, int y) const;

        int GetMaxElevation() const;

        int GetMaxSlopePerTile() const;

        int ClampElevation(int elevation) const;

        int GetMaxAllowedElevation(int x, int y, int currentElevation) const;

        SharedPtr<Theme0::WorldArea> m_worldArea;

        float m_scale;

        Size m_size;
    };
}