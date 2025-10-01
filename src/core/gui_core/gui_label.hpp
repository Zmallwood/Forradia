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
             bool centerAlign = false, color color = colors::WheatTransparent)
        : gui_component(x, y, width, height), m_text(text),
          m_centerAlign(centerAlign), m_color(color) {}

    void SetText(str_view value) { m_text = value; }

  protected:
    virtual void RenderDerived() const override;

  private:
    str m_text;
    bool m_centerAlign{false};
    color m_color;
  };
}
