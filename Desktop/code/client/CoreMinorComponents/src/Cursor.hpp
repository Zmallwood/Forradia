/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "CursorStyles.hpp"
#include "Hash.hpp"

namespace Forradia {
  /**
   * Class for the game cursor, which replaces the default system cursor.
   */
  class Cursor {
   public:
    /**
     * Default constructor
     */
    Cursor() {
      this->Initialize();
    }

    /**
     * Resets the cursor style to normal.
     */
    auto ResetStyleToNormal() -> void;

    /**
     * Renders the cursor.
     */
    auto Render() const -> void;

    /**
     * Sets the cursor style.
     * @param value New cursor style.
     */
    auto SetCursorStyle(CursorStyles value) -> void {
      m_cursorStyle = value;
    }

   private:
    auto Initialize() -> void;

    auto DisableSystemCursor() const -> void;

    constexpr static float k_cursorSize{0.05F};
    const int k_renderID{Hash("RenderIDCursor")};
    CursorStyles m_cursorStyle{CursorStyles::Normal};
  };
}
