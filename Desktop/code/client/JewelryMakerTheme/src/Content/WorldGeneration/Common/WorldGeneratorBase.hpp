/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>

namespace ForradiaEngine::JewelryMakerTheme
{
    class WorldArea;

    /**
     *  Base class for world generators.
     */
    class WorldGeneratorBase
    {
      public:
        /**
         *  Prepare the world generator.
         */
        auto prepare() -> void;

      protected:
        /**
         *  Get the distance between two points.
         *
         *  @param x1 The x coordinate of the first point.
         *  @param y1 The y coordinate of the first point.
         *  @param x2 The x coordinate of the second point.
         *  @param y2 The y coordinate of the second point.
         *  @return The distance between the two points.
         */
        static auto getDistance(int x1, int y1, int x2, int y2) -> float;

        /**
         *  Get the default ground elevation.
         *
         *  @return The default ground elevation.
         */
        [[nodiscard]] constexpr static auto getDefaultGroundElevation()
        {
            return k_defaultGroundElevation;
        }

        /**
         *  Get the world area.
         *
         *  @return The world area.
         */
        [[nodiscard]] auto getWorldArea() const
        {
            return m_worldArea;
        }

        /**
         *  Get the size of the world area.
         *
         *  @return The size of the world area.
         */
        [[nodiscard]] auto getWorldAreaSize() const
        {
            return m_worldAreaSize;
        }

        /**
         *  Get the scale factor of the world.
         *
         *  @return The scale factor of the world.
         */
        [[nodiscard]] auto getWorldScaling() const
        {
            return m_worldScaling;
        }

        /**
         *  Get the world area lower floors.
         *
         *  @return The world area lower floors.
         */
        [[nodiscard]] auto getWorldAreaLowerFloors() const
        {
            return m_worldAreaLowerFloors;
        }

        /**
         *  Get the size of the world area lower floors.
         *
         *  @return The size of the world area lower floors.
         */
        [[nodiscard]] auto getWorldAreaLowerFloorsSize() const
        {
            return m_worldAreaLowerFloorsSize;
        }

        /**
         *  Get the scale factor of the world area lower floors.
         *
         *  @return The scale factor of the world area lower floors.
         */
        [[nodiscard]] auto getWorldScalingLowerFloors() const
        {
            return m_worldScalingLowerFloors;
        }

      private:
        constexpr static int k_defaultGroundElevation{10};
        std::shared_ptr<WorldArea> m_worldArea{};
        std::shared_ptr<WorldArea> m_worldAreaLowerFloors{};
        Size m_worldAreaSize{};
        Size m_worldAreaLowerFloorsSize{};
        float m_worldScaling{};
        float m_worldScalingLowerFloors{};
    };
}
