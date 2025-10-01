/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_panel.hpp"

namespace forr {
  class gui_movable_panel : public gui_panel {
  public:
    gui_movable_panel(float x, float y, float width, float height)
        : gui_panel(x, y, width, height) {}

  protected:
    void UpdateDerived() override;

    void StartMoving();

    void StopMoving();

    virtual rect_f GetDraggableArea();

    auto GetIsBeingMoved() const { return m_isBeingMoved; }

    auto GetMoveStartPosition() const { return m_moveStartPosition; }

    auto GetMoveStartMousePosition() const { return m_moveStartMousePosition; }

  private:
    bool m_isBeingMoved{false};
    point_f m_moveStartPosition{-1, -1};
    point_f m_moveStartMousePosition{-1, -1};
  };
}
