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
  void Reset();

  /**
   * Registers a key as being pressed.
   *
   * @param key Key to register.
   */
  void RegisterKeyPress(SDL_Keycode key);

  /**
   * Registers a key as being released, by unregistering it as being pressed.
   *
   * @param key Key to unregister.
   */
  void RegisterKeyRelease(SDL_Keycode key);

  /**
   * Checks if a key is currently being pressed, without picking the result (I.e. the
   * result can be obtained multiple times after each other).
   *
   * @param key Key to check.
   * @return True if the key is pressed, otherwise false.
   */
  bool KeyIsPressed(SDL_Keycode key) const;

  /**
   * Checks if a key is currently being pressed, and picks the result (I.e. the result
   * can only be obtained once).
   *
   * @param key Key to check.
   * @return True if the key is pressed, otherwise false.
   */
  bool KeyIsPressedPickResult(SDL_Keycode key);

  /**
   * Checks if any key is currently being pressed, and picks the result (I.e. the result
   * can only be obtained once).
   *
   * @return True if any key is pressed, otherwise false.
   */
  bool AnyKeyIsPressedPickResult();

  /**
   * Starts text input.
   */
  void StartTextInput();

  /**
   * Stops text input.
   */
  void StopTextInput();

  /**
   * Adds text to the text input.
   *
   * @param text Text to add.
   */
  void AddTextInput(StringView text);

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