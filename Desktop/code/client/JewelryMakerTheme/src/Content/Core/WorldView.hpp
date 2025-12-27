/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <unordered_map>
    #include <numbers>
    #include <memory>

    #include <glm/glm.hpp>

    #include "ForradiaEngine/Common/General.hpp"
    #include "ForradiaEngine/Common/Matter/Geometry.hpp"
    #include "ForradiaEngine/Rendering/Ground/TileData.hpp"
    #include "ForradiaEngine/Common/Matter/Coloring.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    class WorldArea;

    /**
     *  Renders the world.
     */
    class WorldView
    {
      public:
        static auto instance() -> WorldView &
        {
            static WorldView instance;
            return instance;
        }

        WorldView(const WorldView &) = delete;

        auto operator=(const WorldView &) -> WorldView & = delete;

        /**
         *  Constructor.
         */
        WorldView()
        {
            this->initialize();
        }

        /**
         *  Renders the world.
         */
        auto render() -> void;

      private:
        auto initialize() -> void;

        auto iterationGround(int xPos, int yPos) -> void;

        auto iterationAllExceptGround(int xPos, int yPos) -> void;

        static auto getColorByGroundType(int groundType) -> Color;

        const float k_groundRenderingDistanceMultiplier{1.5F};
        const int k_maxWaterDepthRendering{3};
        const int k_renderIDGroundSymbolHoveredTile{hash("GroundSymbolHoveredTile")};
        const int k_renderIDGroundSymbolTargetedRobot{hash("GroundSymbolTargetedRobot")};
        // 45 degrees up in +Z
        // NOLINTNEXTLINE(readability-magic-numbers)
        constexpr static glm::vec3 k_sunDirectionRaw = glm::vec3(0.7F, 0.0F, 0.7F);
        // 45 degrees
        // NOLINTNEXTLINE(readability-magic-numbers)
        constexpr static float k_sunElevation = std::numbers::pi / 4.0F;
        constexpr static auto k_tilesGroupSize{20};
        glm::vec3 m_sunDirection{};
        std::unordered_map<int, std::unordered_map<int, int>> m_renderIDsGround{};
        std::unordered_map<int, std::unordered_map<int, std::vector<float>>> m_elevationsAll;
        std::vector<TileData> m_tiles{};
        Point m_playerPos{};
        Size m_gridSize{};
        Size m_worldAreaSize{};
        Size m_groundGridSize{};
        std::shared_ptr<WorldArea> m_worldArea{};
        float m_rendTileSize{};
        Point m_hoveredCoordinate{};
    };
}
