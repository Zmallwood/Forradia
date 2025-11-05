//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "MouseButton.hpp"

namespace Forradia
{
    void MouseButton::Reset()
    {
        // Completely reset the state of the button.

        m_pressed = false;

        m_hasBeenFired = false;

        m_hasBeenReleased = false;
    }

    void MouseButton::RegisterPress()
    {
        // Register that the button has been pressed.

        m_pressed = true;

        m_hasBeenFired = true;

        m_ticksFired = GetTicks();
    }

    void MouseButton::RegisterRelease()
    {
        // Register that the button has been released.

        m_pressed = false;

        m_hasBeenReleased = true;

        m_ticksClickSpeed = GetTicks() - m_ticksFired;
    }

    bool MouseButton::IsPressedPickResult()
    {
        // Check if the button is currently pressed
        // and store as result.

        auto result{m_pressed};

        // Clear the pressed state of the button.

        m_pressed = false;

        // Return the result.

        return result;
    }
}