/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
  /**
   * Manages keyboard input from the player.
   */
  class KeyboardInput {
   public:
    /**
     * Resets the keyboard input.
     */
    auto Reset() -> void;

    /**
     * Registers a key as being pressed.
     *
     * @param key Key to register.
     */
    auto RegisterKeyPress(SDL_Keycode key) -> void;

    /**
     * Registers a key as being released, by unregistering it as being pressed.
     *
     * @param key Key to unregister.
     */
    auto RegisterKeyRelease(SDL_Keycode key) -> void;

    /**
     * Checks if a key is currently being pressed, without picking the result (I.e. the
     * result can be obtained multiple times after each other).
     *
     * @param key Key to check.
     * @return True if the key is pressed, otherwise false.
     */
    auto KeyIsPressed(SDL_Keycode key) const -> bool;

    /**
     * Checks if a key is currently being pressed, and picks the result (I.e. the result
     * can only be obtained once).
     *
     * @param key Key to check.
     * @return True if the key is pressed, otherwise false.
     */
    auto KeyIsPressedPickResult(SDL_Keycode key) -> bool;

    /**
     * Checks if any key is currently being pressed, and picks the result (I.e. the result
     * can only be obtained once).
     *
     * @return True if any key is pressed, otherwise false.
     */
    auto AnyKeyIsPressedPickResult() -> bool;

    /**
     * Starts text input.
     */
    auto StartTextInput() -> void;

    /**
     * Stops text input.
     */
    auto StopTextInput() -> void;

    /**
     * Adds text to the text input.
     *
     * @param text Text to add.
     */
    auto AddTextInput(StringView text) -> void;

    /**
     * Returns the text input.
     *
     * @return The text input.
     */
    auto GetTextInput() const {
      return m_textInput;
    }

   private:
    std::set<SDL_Keycode> m_pressed;
    String m_textInput;
  };
}
