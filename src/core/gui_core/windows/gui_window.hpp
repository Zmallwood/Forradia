/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "../gui_movable_panel.hpp"
#include "sub/gui_window_title_bar.hpp"

namespace forr {
  class gui_window : public gui_movable_panel {
  public:
    gui_window(float x, float y, float width, float height,
               str_view windowTitleText)
        : gui_movable_panel(x, y, width, height),
          m_guiWindowTitleBar(*this, windowTitleText) {
      Initialize();
    }

  protected:
    void RenderDerived() const override;

    rect_f GetDraggableArea() override;

  private:
    void Initialize();

    const float k_titleBarHeight{0.04f};

    gui_window_title_bar m_guiWindowTitleBar;
  };
}
