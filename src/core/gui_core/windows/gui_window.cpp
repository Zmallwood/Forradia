/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "gui_window.hpp"

namespace forr {
  void GUIWindow::Initialize() { SetVisible(false); }

  void GUIWindow::RenderDerived() const {
    GUIMovablePanel::RenderDerived();
    m_guiWindowTitleBar.Render();
  }

  RectF GUIWindow::GetDraggableArea() {
    return m_guiWindowTitleBar.GetBounds();
  }
}