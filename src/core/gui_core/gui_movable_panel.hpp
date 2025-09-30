/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "gui_panel.hpp"

namespace Forradia {
  class GUIMovablePanel : public GUIPanel {
  public:
    GUIMovablePanel(float x, float y, float width, float height)
        : GUIPanel(x, y, width, height) {}

  protected:
    void UpdateDerived() override;

    void StartMoving();

    void StopMoving();

    virtual RectF GetDraggableArea();

    auto GetIsBeingMoved() const { return m_isBeingMoved; }

    auto GetMoveStartPosition() const { return m_moveStartPosition; }

    auto GetMoveStartMousePosition() const { return m_moveStartMousePosition; }

  private:
    bool m_isBeingMoved{false};
    PointF m_moveStartPosition{-1, -1};
    PointF m_moveStartMousePosition{-1, -1};
  };
}
