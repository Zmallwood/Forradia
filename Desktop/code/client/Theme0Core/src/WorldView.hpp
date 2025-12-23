/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Hash.hpp"
#include "TileData.hpp"
#include <unordered_map>

namespace Forradia::Theme0
{
    /**
     * Renders the world.
     */
    class WorldView
    {
      public:
        static auto Instance() -> WorldView &
        {
            static WorldView instance;
            return instance;
        }

        // Delete copy/move
        WorldView(const WorldView &) = delete;

        auto operator=(const WorldView &) -> WorldView & = delete;

        /**
         * Constructor.
         */
        WorldView()
        {
            this->Initiallize();
        }

        /**
         * Renders the world.
         */
        auto Render() -> void;

      private:
        auto Initiallize() -> void;

        auto IterationGround(int x, int y) -> void;

        auto IterationAllExceptGround(int x, int y) -> void;

        const float k_groundRenderingDistanceMultiplier{1.5F};
        const int k_maxWaterDepthRendering{3};
        const int k_renderIDGroundSymbolHoveredTile{Hash("GroundSymbolHoveredTile")};
        const int k_renderIDGroundSymbolTargetedRobot{Hash("GroundSymbolTargetedRobot")};
        std::unordered_map<int, std::unordered_map<int, int>> m_renderIDsGround{};
        std::unordered_map<int, std::unordered_map<int, std::vector<float>>> m_elevationsAll;
        std::vector<TileData> m_tiles;
    };
}
