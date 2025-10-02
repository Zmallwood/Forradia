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
               str_view background_image = k_background_image,
               str_view hovered_background_image = k_hovered_background_image)
        : gui_panel(x, y, width, height), m_text(text), m_action(action),
          m_background_image(background_image),
          m_hovered_background_image(hovered_background_image) {}

   protected:
    virtual void update_derived() override;

    virtual void render_derived() const override;

   private:
    inline static const str k_background_image{"GUIButtonBackground"};
    inline static const str k_hovered_background_image{
        "GUIButtonHoveredBackground"};

    str m_text;
    func<void()> m_action;
    str m_background_image;
    str m_hovered_background_image;
  };
}
