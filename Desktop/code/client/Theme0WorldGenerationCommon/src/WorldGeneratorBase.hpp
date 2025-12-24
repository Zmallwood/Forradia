/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0
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

      private:
        constexpr static int k_defaultGroundElevation{10};
        std::shared_ptr<WorldArea> m_worldArea{};
        Size m_worldAreaSize{};
        float m_worldScaling{};
    };
}
