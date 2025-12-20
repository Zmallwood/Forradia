/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    /**
     * Renders the world.
     */
    class WorldView {
      public:
        /**
         * Constructor.
         */
        WorldView() {
            this->Initiallize();
        }

        /**
         * Renders the world.
         */
        auto Render() const -> void;

      private:
        auto Initiallize() -> void;

        const float k_groundRenderingDistanceMultiplier{1.5f};
        const int k_maxWaterDepthRendering{3};
        const int k_renderIDGroundSymbolHoveredTile{Hash("GroundSymbolHoveredTile")};
        const int k_renderIDGroundSymbolTargetedRobot{Hash("GroundSymbolTargetedRobot")};
        std::unordered_map<int, std::unordered_map<int, int>> m_renderIDsGround;
        std::unordered_map<int, std::unordered_map<int, int>> m_renderIDsClaimedTiles;
    };
}
