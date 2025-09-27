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
    }

    void MouseButton::RegisterPress()
    {
        m_isPressed = true;
    }

    void MouseButton::RegisterRelease()
    {
        m_isPressed = false;
    }

    bool MouseButton::IsPressedPickResult()
    {
        auto isPressedResult{m_isPressed};

        m_isPressed = false;

        return isPressedResult;
    }
}