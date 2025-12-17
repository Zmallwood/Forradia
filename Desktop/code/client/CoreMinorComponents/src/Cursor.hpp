/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "CursorStyles.hpp"

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
  void ResetStyleToNormal();

  /**
   * Renders the cursor.
   */
  void Render() const;

  /**
   * Sets the cursor style.
   * @param value New cursor style.
   */
  void SetCursorStyle(CursorStyles value) {
    m_cursorStyle = value;
  }

 private:
  void Initialize();

  void DisableSystemCursor() const;

  constexpr static float k_cursorSize{0.05f};
  const int k_renderID{Hash("RenderIDCursor")};
  CursorStyles m_cursorStyle{CursorStyles::Normal};
};
}