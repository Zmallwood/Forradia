/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_component.hpp"

namespace forr {
  class gui_panel : public gui_component {
   public:
    gui_panel(float x, float y, float w, float h,
              str_view bg_img = k_default_bg_img)
        : gui_component(x, y, w, h), m_bg_img(bg_img) {}

   protected:
    virtual void render_derived() const override;

    void set_background_image(str_view val) { m_bg_img = val; }

   private:
    inline static const str k_default_bg_img{"GUIPanelBackground"};

    str m_bg_img;
  };
}
