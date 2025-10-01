/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "sub/cursor_styles.hpp"

namespace forr {
  class cursor {
  public:
    cursor() { Initialize(); }

    void ResetStyleToDefault();

    void Render();

    auto SetCursorStyle(cursor_styles value) { m_cursorStyle = value; }

  private:
    void Initialize();

    void DisableSystemCursor();

    constexpr static float k_cursorSize{0.05f};

    cursor_styles m_cursorStyle{cursor_styles::Default};
  };
}