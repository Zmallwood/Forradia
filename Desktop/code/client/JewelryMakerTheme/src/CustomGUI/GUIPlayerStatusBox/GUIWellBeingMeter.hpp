/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/Common/Matter/Coloring.hpp"
#include "ForradiaEngine/GUICore/GUIMeter.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Represents the well-being meter.
     */
    class GUIWellBeingMeter : public GUIMeter
    {
      public:
        /**
         *  Constructor.
         *
         *  @param x The x coordinate of the meter.
         *  @param y The y coordinate of the meter.
         *  @param width The width of the meter.
         *  @param height The height of the meter.
         */
        GUIWellBeingMeter(float xPos, float yPos, float width, float height)
            : GUIMeter("GUIWellBeingMeter", xPos, yPos, width, height, getFilledColor())
        {
        }

        /**
         *  Gets the height of the meter.
         *
         *  @return The height of the meter.
         */
        static auto getHeight()
        {
            return k_height;
        }

      protected:
        /**
         *  Does update logic that is specific to the well-being meter.
         */
        auto updateDerived() -> void override;

        /**
         *  Gets the filled percentage of the meter.
         *
         *  @return The filled percentage of the meter.
         */
        auto getFilledPercentage() const -> float override;

        /**
         *  Gets the filled color of the meter.
         *
         *  @return The filled color of the meter.
         */
        static auto getFilledColor() -> Color
        {
            return Palette::getColor<hash("Red")>();
        }

      private:
        constexpr static float k_height{0.02F};
        float m_filledPercentage{0.0F};
    };
}
