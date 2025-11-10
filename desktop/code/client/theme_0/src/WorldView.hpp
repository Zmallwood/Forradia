//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0::GameplayCore
{
    class WorldView
    {
      public:
        WorldView()
        {
            this->Initiallize();
        }

        void Render() const;

      private:
        void Initiallize();

        // Multiplier for ground rendering distance (1.5 = 50% more distance)
        // Ground tiles are rendered at this extended distance, while objects/creatures
        // are still rendered at the normal grid size to maintain performance
        const float k_groundRenderingDistanceMultiplier{1.5f};

        const int k_maxWaterDepthRendering{3};

        const int k_renderIDGroundSymbolHoveredTile{Hash("GroundSymbolHoveredTile")};

        std::map<int, std::map<int, int>> m_renderIDsGround;

        std::map<int, std::map<int, std::map<int, int>>> m_renderIDsWaterDepth;
    };
}