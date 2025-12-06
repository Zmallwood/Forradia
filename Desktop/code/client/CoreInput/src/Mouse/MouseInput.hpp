//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "MouseButton.hpp"

namespace Forradia
{
    ///
    /// Manages mouse input from the player.
    ///
    class MouseInput
    {
      public:
        ///
        /// Resets the state of the mouse input.
        ///
        void Reset();

        ///
        /// Registers a mouse button as being pressed.
        ///
        /// @param button Button to register.
        ///
        void RegisterMouseButtonDown(Uint8 button);

        ///
        /// Registers a mouse button as being released.
        ///
        /// @param button Button to register.
        ///
        void RegisterMouseButtonUp(Uint8 button);

        ///
        /// Checks if any mouse button is currently pressed, picking the result (I.e. the result
        /// can only be obtained once).
        ///
        /// @return True if any mouse button is pressed, otherwise false.
        ///
        bool AnyMouseButtonIsPressedPickResult();

        ///
        /// Adds a mouse wheel delta to the current mouse wheel delta.
        ///
        /// @param delta Mouse wheel delta to add.
        ///
        void AddMouseWheelDelta(int delta);

        ///
        /// Returns the current mouse wheel delta, picking the result (I.e. the result can only
        /// be obtained once).
        ///
        /// @return Current mouse wheel delta.
        ///
        int GetMouseWheelDeltaPickResult();

        ///
        /// Returns a reference to the left mouse button.
        ///
        /// @return Reference to the left mouse button.
        ///
        auto &GetLeftMouseButtonRef()
        {
            return m_leftMouseButton;
        }

        ///
        /// Returns a reference to the right mouse button.
        ///
        /// @return Reference to the right mouse button.
        ///
        auto &GetRightMouseButtonRef()
        {
            return m_rightMouseButton;
        }

      private:
        MouseButton m_leftMouseButton; ///< Left mouse button.

        MouseButton m_rightMouseButton; ///< Right mouse button.

        int m_mouseWheelDelta{0}; ///< Mouse wheel scroll delta.
    };
}