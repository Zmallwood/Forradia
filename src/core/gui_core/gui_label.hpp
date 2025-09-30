/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "gui_component.hpp"

namespace Forradia {
  class GUILabel : public GUIComponent {
  public:
    GUILabel(float x, float y, float width, float height, StringView text = "",
             bool centerAlign = false, Color color = Colors::WheatTransparent)
        : GUIComponent(x, y, width, height), m_text(text),
          m_centerAlign(centerAlign), m_color(color) {}

    void SetText(StringView value) { m_text = value; }

  protected:
    virtual void RenderDerived() const override;

  private:
    String m_text;
    bool m_centerAlign{false};
    Color m_color;
  };
}
