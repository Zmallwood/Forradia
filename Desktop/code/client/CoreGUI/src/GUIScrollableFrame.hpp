/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "GUIComponent.hpp"

namespace Forradia {
  class GUIScrollableFrame : public GUIComponent {
   public:
    GUIScrollableFrame(std::string_view uniqueName, float x, float y, float width, float height)
        : GUIComponent(x, y, width, height),
          k_renderIDUpArrow(Hash(uniqueName.data() + std::string("_UpArrow"))),
          k_renderIDDownArrow(Hash(uniqueName.data() + std::string("_DownArrow"))) {
    }

   protected:
    virtual auto Render() const -> void override;

   private:
    const int k_renderIDUpArrow;
    const int k_renderIDDownArrow;
    float m_scrollPosition{0.0F};
  };
}
