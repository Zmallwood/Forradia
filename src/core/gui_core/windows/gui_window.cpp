/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_window.hpp"

namespace forr {
  void gui_window::Initialize() { SetVisible(false); }

  void gui_window::RenderDerived() const {
    gui_movable_panel::RenderDerived();
    m_guiWindowTitleBar.Render();
  }

  rect_f gui_window::GetDraggableArea() {
    return m_guiWindowTitleBar.GetBounds();
  }
}