/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "Coloring/Color.hpp"
#include "GUIComponent.hpp"
#include "Hash.hpp"

namespace Forradia
{
    /**
     * A meter component for the GUI.
     */
    class GUIMeter : public GUIComponent
    {
      public:
        /**
         * Constructor.
         *
         * @param uniqueName A unique name for the meter.
         * @param xPos The x-coordinate of the meter.
         * @param yPos The y-coordinate of the meter.
         * @param width The width of the meter.
         * @param height The height of the meter.
         * @param filledColor The color of the filled part of the meter.
         */
        GUIMeter(std::string_view uniqueName, float xPos, float yPos, float width, float height,
                 Color filledColor)
            : GUIComponent(xPos, yPos, width, height), k_renderIDBackground(Hash(uniqueName)),
              k_renderIDFilled(Hash(uniqueName.data() + std::string("Filled"))),
              k_renderIDLineTop(Hash(uniqueName.data() + std::string("TopBorder"))),
              k_renderIDLineBottom(Hash(uniqueName.data() + std::string("BottomBorder"))),
              k_renderIDLineRight(Hash(uniqueName.data() + std::string("RightBorder"))),
              k_renderIDLineLeft(Hash(uniqueName.data() + std::string("LeftBorder"))),
              k_filledColor(filledColor)
        {
        }

      protected:
        /**
         * Render tasks specific to the meter, called by the GUIComponent base class.
         */
        auto RenderDerived() const -> void override;

        /**
         * Gets the filled percentage of the meter.
         *
         * @return The filled percentage of the meter.
         */
        virtual auto GetFilledPercentage() const -> float = 0;

      private:
        const float k_borderWidth{0.002F};
        const int k_renderIDBackground{};
        const int k_renderIDFilled{};
        const int k_renderIDLineTop{};
        const int k_renderIDLineBottom{};
        const int k_renderIDLineRight{};
        const int k_renderIDLineLeft{};
        const Color k_filledColor{};
    };
}
