/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_panel.hpp"

namespace forr {
  class gui_button : public gui_panel {
   public:
    gui_button(float x, float y, float w, float h, str_view text,
               func<void()> action, str_view bg_img = k_bg_img,
               str_view hovered_bg_img = k_hovered_bg_img)
        : gui_panel(x, y, w, h), m_text(text), m_action(action),
          m_bg_img(bg_img), m_hovered_bg_img(hovered_bg_img) {}

   protected:
    virtual void update_derived() override;

    virtual void render_derived() const override;

   private:
    inline static const str k_bg_img{"GUIButtonBackground"};
    inline static const str k_hovered_bg_img{"GUIButtonHoveredBackground"};

    str m_text;
    func<void()> m_action;
    str m_bg_img;
    str m_hovered_bg_img;
  };
}
