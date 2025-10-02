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
              str_view background_image = k_default_background_image)
        : gui_component(x, y, width, height),
          m_background_image(background_image) {}

  protected:
    virtual void render_derived() const override;

    void set_background_image(str_view value) { m_background_image = value; }

  private:
    inline static const str k_default_background_image{"GUIPanelBackground"};

    str m_background_image;
  };
}
