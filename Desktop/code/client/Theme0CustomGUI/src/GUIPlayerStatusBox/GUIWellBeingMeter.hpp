/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIMeter.hpp"

namespace Forradia::Theme0
{
    /**
     * Represents the well-being meter.
     */
    class GUIWellBeingMeter : public GUIMeter
    {
      public:
        /**
         * Constructor.
         *
         * @param x The x coordinate of the meter.
         * @param y The y coordinate of the meter.
         * @param width The width of the meter.
         * @param height The height of the meter.
         */
        GUIWellBeingMeter(float x, float y, float width, float height)
            : GUIMeter("GUIWellBeingMeter", x, y, width, height, GetFilledColor())
        {
        }

        /**
         * Gets the height of the meter.
         *
         * @return The height of the meter.
         */
        static auto GetHeight()
        {
            return k_height;
        }

      protected:
        /**
         * Does update logic that is specific to the well-being meter.
         */
        auto UpdateDerived() -> void override;

        /**
         * Gets the filled percentage of the meter.
         *
         * @return The filled percentage of the meter.
         */
        auto GetFilledPercentage() const -> float override;

        /**
         * Gets the filled color of the meter.
         *
         * @return The filled color of the meter.
         */
        static auto GetFilledColor() -> Color
        {
            return Palette::GetColor<Hash("Red")>();
        }

      private:
        constexpr static float k_height{0.02f};
        float m_filledPercentage{0.0f};
    };
}
