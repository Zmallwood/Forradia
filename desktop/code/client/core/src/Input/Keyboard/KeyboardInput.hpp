//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// Manages keyboard input from the player.
    ///
    class KeyboardInput
    {
      public:
        ///
        /// Resets the keyboard input.
        ///
        void Reset();

        ///
        /// Registers a key as being pressed.
        ///
        /// @param key Key to register.
        ///
        void RegisterKeyPress(SDL_Keycode key);

        ///
        /// Registers a key as being released, by
        /// unregistering it as being pressed.
        ///
        /// @param key Key to unregister.
        ///
        void RegisterKeyRelease(SDL_Keycode key);

        ///
        /// Checks if a key is currently being pressed,
        /// without picking the result (I.e. the result can
        /// be obtained multiple times after each other).
        ///
        /// @param key Key to check.
        /// @return True if the key is pressed, otherwise
        /// false.
        ///
        bool KeyIsPressed(SDL_Keycode key) const;

        ///
        /// Checks if a key is currently being pressed,
        /// and picks the result (I.e. the result can only
        /// be obtained once).
        ///
        /// @param key Key to check.
        /// @return True if the key is pressed, otherwise
        /// false.
        ///
        bool KeyIsPressedPickResult(SDL_Keycode key);

        ///
        /// Checks if any key is currently being pressed,
        /// and picks the result (I.e. the result can only
        /// be obtained once).
        ///
        /// @return True if any key is pressed, otherwise
        /// false.
        bool AnyKeyIsPressedPickResult();

      private:
        std::set<SDL_Keycode>
            m_pressed; ///< The set of keys currently being
                       ///< pressed.
    };
}