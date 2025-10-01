/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_component.hpp"

namespace forr {
  class gui_panel : public gui_component {
  public:
    gui_panel(float x, float y, float width, float height,
              str_view backgroundImage = k_defaultBackgroundImage)
        : gui_component(x, y, width, height),
          m_backgroundImage(backgroundImage) {}

  protected:
    virtual void render_derived() const override;

    void set_background_image(str_view value) { m_backgroundImage = value; }

  private:
    inline static const str k_defaultBackgroundImage{"GUIPanelBackground"};

    str m_backgroundImage;
  };
}
