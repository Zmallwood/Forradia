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
            this->Initialize();
        }

        /**
         * Renders the world.
         */
        auto Render() -> void;

      private:
        auto Initialize() -> void;

        auto IterationGround(int xPos, int yPos) -> void;

        auto IterationAllExceptGround(int xPos, int yPos) -> void;

        static auto GetColorByGroundType(int groundType) -> Color;

        const float k_groundRenderingDistanceMultiplier{1.5F};
        const int k_maxWaterDepthRendering{3};
        const int k_renderIDGroundSymbolHoveredTile{Hash("GroundSymbolHoveredTile")};
        const int k_renderIDGroundSymbolTargetedRobot{Hash("GroundSymbolTargetedRobot")};
        // 45 degrees up in +Z
        // NOLINTNEXTLINE(readability-magic-numbers)
        constexpr static glm::vec3 k_sunDirectionRaw = glm::vec3(0.7F, 0.0F, 0.7F);
        // 45 degrees
        // NOLINTNEXTLINE(readability-magic-numbers)
        constexpr static float k_sunElevation = M_PI / 4.0F;
        constexpr static auto k_tilesGroupSize{20};
        glm::vec3 m_sunDirection;
        std::unordered_map<int, std::unordered_map<int, int>> m_renderIDsGround{};
        std::unordered_map<int, std::unordered_map<int, std::vector<float>>> m_elevationsAll;
        std::vector<TileData> m_tiles;
    };
}
