/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "../gui_movable_panel.hpp"
#include "sub/gui_window_title_bar.hpp"

namespace Forradia {
  class GUIWindow : public GUIMovablePanel {
  public:
    GUIWindow(float x, float y, float width, float height,
              StringView windowTitleText)
        : GUIMovablePanel(x, y, width, height),
          m_guiWindowTitleBar(*this, windowTitleText) {
      Initialize();
    }

  protected:
    void RenderDerived() const override;

    RectF GetDraggableArea() override;

  private:
    void Initialize();

    const float k_titleBarHeight{0.04f};

    GUIWindowTitleBar m_guiWindowTitleBar;
  };
}
