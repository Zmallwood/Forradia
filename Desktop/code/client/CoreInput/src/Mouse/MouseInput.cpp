//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "MouseInput.hpp"

namespace Forradia
{
    void MouseInput::Reset()
    {
        // Completely reset the state of the two mouse buttons.

        m_leftMouseButton.Reset();

        m_rightMouseButton.Reset();
    }

    bool MouseInput::AnyMouseButtonIsPressedPickResult()
    {
        // Check if the left mouse button is currently pressed and store as result.

        auto result{m_leftMouseButton.IsPressedPickResult()};

        // Also check if the right mouse button is currently pressed and add to the result using
        // a logical OR.

        result |= m_rightMouseButton.IsPressedPickResult();

        // Return the result.

        return result;
    }

    void MouseInput::AddMouseWheelDelta(int delta)
    {
        // Add the mouse wheel delta to the current mouse wheel delta.

        m_mouseWheelDelta += delta;
    }

    int MouseInput::GetMouseWheelDeltaPickResult()
    {
        // Get the current mouse wheel delta and store as result.

        auto result{m_mouseWheelDelta};

        // Reset the mouse wheel delta.

        m_mouseWheelDelta = 0;

        // Return the result.

        return result;
    }
}