/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once
#include "GUIComponent.hpp"

namespace Forradia {
    class GUIScrollableArea : public GUIComponent {
      public:
        GUIScrollableArea(std::string_view uniqueName, float x, float y, float width, float height)
            : GUIComponent(x, y, width, height),
              k_renderIDUpArrow(Hash(uniqueName.data() + std::string("_UpArrow"))),
              k_renderIDDownArrow(Hash(uniqueName.data() + std::string("_DownArrow"))),
              k_renderIDSlider(Hash(uniqueName.data() + std::string("_Slider"))) {
        }

      protected:
        virtual auto OnMouseDown(Uint8 mouseButton) -> bool override;

        virtual auto OnMouseUp(Uint8 mouseButton, int clickSpeed) -> bool override;

        virtual auto UpdateDerived() -> void override;

        virtual auto Render() const -> void override;

        auto GetBounds() const -> RectF override;

      private:
        auto GetUpArrowBounds() const -> RectF;

        auto GetDownArrowBounds() const -> RectF;

        auto GetSliderBounds() const -> RectF;

        const int k_renderIDUpArrow;
        const int k_renderIDDownArrow;
        const int k_renderIDSlider;
        const float k_scrollbarWidth{0.02F};
        const float k_sliderHeight{0.08F};
        float m_scrollPosition{0.0F};
        bool m_movingSlider{false};
        float m_sliderStartMoveYPos{-1.0f};
        float m_sliderStartMoveMouseYPos{-1.0f};
    };
}
