//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0::GameplayCore {
    class WorldView {
      public:
        WorldView() {
            this->Initiallize();
        }

        void Render() const;

      private:
        void Initiallize();

        const float k_groundRenderingDistanceMultiplier{1.5f};
        const int k_maxWaterDepthRendering{3};
        const int k_renderIDGroundSymbolHoveredTile{Hash("GroundSymbolHoveredTile")};
        const int k_renderIDGroundSymbolTargetedRobot{Hash("GroundSymbolTargetedRobot")};
        std::map<int, std::map<int, int>> m_renderIDsGround;
        std::map<int, std::map<int, int>> m_renderIDsClaimedTiles;
        std::map<int, std::map<int, int>> m_renderIDsRivers1;
        std::map<int, std::map<int, int>> m_renderIDsRivers2;
    };
}