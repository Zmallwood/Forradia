/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_component.hpp"

namespace forr {
  class gui_label : public gui_component {
   public:
    gui_label(float x, float y, float w, float h, str_view text = "",
              bool cent_align = false, color color = colors::wheat_transp)
        : gui_component(x, y, w, h), m_text(text), m_cent_align(cent_align),
          m_color(color) {}

    void set_text(str_view val) { m_text = val; }

   protected:
    virtual void render_derived() const override;

   private:
    str m_text;
    bool m_cent_align{false};
    color m_color;
  };
}
