/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_panel.hpp"

namespace forr {
  class gui_button : public gui_panel {
  public:
    gui_button(float x, float y, float width, float height, str_view text,
               func<void()> action,
               str_view backgroundImage = k_backgroundImage,
               str_view hoveredBackgroundImage = k_hoveredBackgroundImage)
        : gui_panel(x, y, width, height), m_text(text), m_action(action),
          m_backgroundImage(backgroundImage),
          m_hoveredBackgroundImage(hoveredBackgroundImage) {}

  protected:
    virtual void update_derived() override;

    virtual void render_derived() const override;

  private:
    inline static const str k_backgroundImage{"GUIButtonBackground"};
    inline static const str k_hoveredBackgroundImage{
        "GUIButtonHoveredBackground"};

    str m_text;
    func<void()> m_action;
    str m_backgroundImage;
    str m_hoveredBackgroundImage;
  };
}
