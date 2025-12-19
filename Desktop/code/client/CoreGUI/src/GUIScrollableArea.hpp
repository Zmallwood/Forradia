/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

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
    virtual auto Render() const -> void override;

   private:
    const int k_renderIDUpArrow;
    const int k_renderIDDownArrow;
    const int k_renderIDSlider;
    float m_scrollPosition{0.0F};
  };
}
