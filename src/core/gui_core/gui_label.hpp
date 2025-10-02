/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_component.hpp"

namespace forr {
  class gui_label : public gui_component {
  public:
    gui_label(float x, float y, float width, float height, str_view text = "",
              bool center_align = false, color color = colors::wheat_transp)
        : gui_component(x, y, width, height), m_text(text),
          m_center_align(center_align), m_color(color) {}

    void set_text(str_view value) { m_text = value; }

  protected:
    virtual void render_derived() const override;

  private:
    str m_text;
    bool m_center_align{false};
    color m_color;
  };
}
