/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MouseButton.hpp"

namespace Forradia
{
    void MouseButton::Reset()
    {
        m_isPressed = false;

        m_hasBeenFired = false;

        m_hasBeenReleased = false;
    }

    void MouseButton::RegisterPress()
    {
        m_isPressed = true;

        m_hasBeenFired = true;
    }

    void MouseButton::RegisterRelease()
    {
        m_isPressed = false;

        m_hasBeenReleased = true;
    }

    bool MouseButton::IsPressedPickResult()
    {
        auto isPressedResult{m_isPressed};

        m_isPressed = false;

        return isPressedResult;
    }

    bool MouseButton::GetHasBeenFiredPickResult()
    {
        auto hasBeenFiredResult {m_hasBeenFired};

        m_hasBeenFired = false;

        return hasBeenFiredResult;
    }

    bool MouseButton::GetHasBeenFiredDontPickResult()
    {
        return m_hasBeenFired;
    }

    bool MouseButton::GetHasBeenReleasedPickResult()
    {
        auto hasBeenReleasedResult {m_hasBeenReleased};

        m_hasBeenReleased = false;

        return hasBeenReleasedResult;
    }

    bool MouseButton::GetHasBeenReleasedDontPickResult()
    {
        return m_hasBeenReleased;
    }
}