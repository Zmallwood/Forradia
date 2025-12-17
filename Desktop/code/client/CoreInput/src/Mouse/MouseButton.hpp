/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/**
 * Represents a mouse button.
 */
class MouseButton {
 public:
  /**
   * Resets the state of the button.
   */
  auto Reset() -> void;

  /**
   * Registers that the button has been pressed.
   */
  auto RegisterPress() -> void;

  /**
   * Registers that the button has been released.
   */
  auto RegisterRelease() -> void;

  /**
   * Checks if the button is currently being pressed, picking the result (I.e. the result
   * can only be obtained once).
   *
   * @return True if the button is pressed, otherwise false.
   */
  auto IsPressedPickResult() -> bool;

  /**
   * Checks if the button has been fired, picking the result (I.e. the result can only be
   * obtained once).
   *
   * @return True if the button has been fired, otherwise false.
   */
  auto HasBeenFiredPickResult() -> bool;

  /**
   * Checks if the button has been fired, without picking the result (I.e. the result can
   * be obtained multiple times after each other).
   *
   * @return True if the button has been fired, otherwise false.
   */
  auto HasBeenFired() const -> bool;

  /**
   * Checks if the button has been released, picking the result (I.e. the result can only
   * be obtained once).
   *
   * @return True if the button has been released, otherwise false.
   */
  auto HasBeenReleasedPickResult() -> bool;

  /**
   * Checks if the button has been released, without picking the result (I.e. the result
   * can be obtained multiple times after each other).
   *
   * @return True if the button has been released, otherwise false.
   */
  auto HasBeenReleased() const -> bool;

  /**
   * Returns the speed of the most recent click.
   *
   * @return The speed of the most recent click.
   */
  auto GetTicksClickSpeed() const {
    return m_ticksClickSpeed;
  }

 private:
  bool m_pressed{false};
  bool m_hasBeenFired{false};
  bool m_hasBeenReleased{false};
  int m_ticksFired{0};
  int m_ticksClickSpeed{0};
};
}
