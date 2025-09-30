/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "GUIPanel.hpp"

namespace Forradia {
  class GUIButton : public GUIPanel {
  public:
    GUIButton(float x, float y, float width, float height, StringView text,
              Function<void()> action,
              StringView backgroundImage = k_backgroundImage,
              StringView hoveredBackgroundImage = k_hoveredBackgroundImage)
        : GUIPanel(x, y, width, height), m_text(text), m_action(action),
          m_backgroundImage(backgroundImage),
          m_hoveredBackgroundImage(hoveredBackgroundImage) {}

  protected:
    virtual void UpdateDerived() override;

    virtual void RenderDerived() const override;

  private:
    inline static const String k_backgroundImage{"GUIButtonBackground"};
    inline static const String k_hoveredBackgroundImage{
        "GUIButtonHoveredBackground"};

    String m_text;
    Function<void()> m_action;
    String m_backgroundImage;
    String m_hoveredBackgroundImage;
  };
}
