//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace AAK
{
    namespace Forradia
    {
        ///
        /// Represents a mouse button.
        ///
        class MouseButton
        {
          public:
            ///
            /// Resets the state of the button.
            ///
            void Reset();

            ///
            /// Registers that the button has been pressed.
            ///
            void RegisterPress();

            ///
            /// Registers that the button has been released.
            ///
            void RegisterRelease();

            ///
            /// Checks if the button is currently being pressed, picking the result (I.e. the result
            /// can only be obtained once).
            ///
            /// @return True if the button is pressed, otherwise false.
            ///
            bool IsPressedPickResult();

            ///
            /// Checks if the button has been fired, picking the result (I.e. the result can only be
            /// obtained once).
            ///
            /// @return True if the button has been fired, otherwise false.
            ///
            bool HasBeenFiredPickResult();

            ///
            /// Checks if the button has been fired, without picking the result (I.e. the result can
            /// be obtained multiple times after each other).
            ///
            /// @return True if the button has been fired, otherwise false.
            ///
            bool HasBeenFired() const;

            ///
            /// Checks if the button has been released, picking the result (I.e. the result can only
            /// be obtained once).
            ///
            /// @return True if the button has been released, otherwise false.
            ///
            bool HasBeenReleasedPickResult();

            ///
            /// Checks if the button has been released, without picking the result (I.e. the result
            /// can be obtained multiple times after each other).
            ///
            /// @return True if the button has been released, otherwise false.
            ///
            bool HasBeenReleased() const;

            ///
            /// Returns the speed of the most recent click.
            ///
            /// @return The speed of the most recent click.
            ///
            auto GetTicksClickSpeed() const
            {
                return m_ticksClickSpeed;
            }

          private:
            bool m_pressed{false}; ///< True if the button is currently pressed.

            bool m_hasBeenFired{false}; ///< True if the button has been fired.

            bool m_hasBeenReleased{false}; ///< True if the button has been released.

            int m_ticksFired{0}; ///< The point in time, as ticks, when the button was last fired.

            int m_ticksClickSpeed{0}; ///< The speed of the most recent click.
        };
    }
}