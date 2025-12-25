/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "GUIComponent.hpp"
    #include "ForradiaEngine/Common/General/Hash.hpp"
// clang-format on

namespace Forradia
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
        auto onMouseDown(Uint8 mouseButton) -> bool override;

        auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool override;

        auto updateDerived() -> void override;

        auto render() const -> void override;

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
