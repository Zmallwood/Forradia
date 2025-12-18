/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "MouseButton.hpp"

namespace Forradia {
  /**
   * Manages mouse input from the player.
   */
  class MouseInput {
   public:
    /**
     * Resets the state of the mouse input.
     */
    auto Reset() -> void;

    /**
     * Registers a mouse button as being pressed.
     *
     * @param button Button to register.
     */
    auto RegisterMouseButtonDown(Uint8 button) -> void;

    /**
     * Registers a mouse button as being released.
     *
     * @param button Button to register.
     */
    auto RegisterMouseButtonUp(Uint8 button) -> void;

    /**
     * Checks if any mouse button is currently pressed, picking the result (I.e. the result
     * can only be obtained once).
     *
     * @return True if any mouse button is pressed, otherwise false.
     */
    auto AnyMouseButtonIsPressedPickResult() -> bool;

    /**
     * Adds a mouse wheel delta to the current mouse wheel delta.
     *
     * @param delta Mouse wheel delta to add.
     */
    auto AddMouseWheelDelta(int delta) -> void;

    /**
     * Returns the current mouse wheel delta, picking the result (I.e. the result can only
     * be obtained once).
     *
     * @return Current mouse wheel delta.
     */
    auto GetMouseWheelDeltaPickResult() -> int;

    /**
     * Returns a reference to the left mouse button.
     *
     * @return Reference to the left mouse button.
     */
    auto &GetLeftMouseButtonRef() {
      return m_leftMouseButton;
    }

    /**
     * Returns a reference to the right mouse button.
     *
     * @return Reference to the right mouse button.
     */
    auto &GetRightMouseButtonRef() {
      return m_rightMouseButton;
    }

   private:
    MouseButton m_leftMouseButton;
    MouseButton m_rightMouseButton;
    int m_mouseWheelDelta{0};
  };
}
