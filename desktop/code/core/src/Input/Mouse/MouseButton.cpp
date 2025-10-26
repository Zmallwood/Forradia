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
        m_pressed = false;

        m_hasBeenFired = false;

        m_hasBeenReleased = false;
    }

    void MouseButton::RegisterPress()
    {
        m_pressed = true;

        m_hasBeenFired = true;
    }

    void MouseButton::RegisterRelease()
    {
        m_pressed = false;

        m_hasBeenReleased = true;
    }

    bool MouseButton::IsPressedPickResult()
    {
        auto result{m_pressed};

        m_pressed = false;

        return result;
    }

    bool MouseButton::HasBeenFiredPickResult()
    {
        auto result{m_hasBeenFired};

        m_hasBeenFired = false;

        return result;
    }

    bool MouseButton::HasBeenFired()
    {
        return m_hasBeenFired;
    }

    bool MouseButton::HasBeenReleasedPickResult()
    {
        auto result{m_hasBeenReleased};

        m_hasBeenReleased = false;

        return result;
    }

    bool MouseButton::HasBeenReleased()
    {
        return m_hasBeenReleased;
    }
}