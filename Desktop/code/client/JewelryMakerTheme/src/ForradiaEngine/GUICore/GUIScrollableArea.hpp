/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIComponent.hpp"
#include "ForradiaEngine/Common/General.hpp"

namespace ForradiaEngine
{
    class GUIScrollableArea : public GUIComponent
    {
      public:
        GUIScrollableArea(std::string_view uniqueName, float xPos, float yPos, float width,
                          float height)
            : GUIComponent(xPos, yPos, width, height),
              k_renderIDUpArrow(hash(uniqueName.data() + std::string("_UpArrow"))),
              k_renderIDDownArrow(hash(uniqueName.data() + std::string("_DownArrow"))),
              k_renderIDSlider(hash(uniqueName.data() + std::string("_Slider")))
        {
        }

      protected:
        /**
         *  Handles the mouse down event.
         *
         *  @param mouseButton The mouse button that was pressed.
         *  @return True if the mouse down event was handled, false otherwise.
         *  (Note: currently it only returns false, look at the implementation to see why.)
         */
        auto onMouseDown(Uint8 mouseButton) -> bool override;

        /**
         *  Handles the mouse up event.
         *
         *  @param mouseButton The mouse button that was released.
         *  @param clickSpeed The speed of the click.
         *  @return True if the mouse up event was handled, false otherwise.
         */
        auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool override;

        // TODO: Consider implementing this.
        // auto onMouseWheel(int delta) -> bool override;

        /**
         *  Update tasks specific to the scrollable area.
         */
        auto updateDerived() -> void override;

        /**
         *  Render tasks specific to the scrollable area.
         */
        auto render() const -> void override;

        /**
         *  Gets the bounds of the scrollable area.
         *
         *  @return The bounds of the scrollable area.
         */
        auto getBounds() const -> RectF override;

      private:
        auto getUpArrowBounds() const -> RectF;

        auto getDownArrowBounds() const -> RectF;

        auto getSliderBounds() const -> RectF;

        const int k_renderIDUpArrow{};
        const int k_renderIDDownArrow{};
        const int k_renderIDSlider{};
        const float k_scrollbarMoveStepSize{0.05F};
        const float k_scrollbarWidth{0.02F};
        const float k_sliderHeight{0.08F};
        float m_scrollPosition{0.0F};
        bool m_movingSlider{false};
        float m_sliderStartMoveYPos{-1.0F};
        float m_sliderStartMoveMouseYPos{-1.0F};
    };
}
