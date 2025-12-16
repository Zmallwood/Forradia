//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "MouseInput.hpp"

namespace Forradia {
    void MouseInput::Reset() {
        m_leftMouseButton.Reset();
        m_rightMouseButton.Reset();
    }

    bool MouseInput::AnyMouseButtonIsPressedPickResult() {
        auto result{m_leftMouseButton.IsPressedPickResult()};
        result |= m_rightMouseButton.IsPressedPickResult();
        return result;
    }

    void MouseInput::AddMouseWheelDelta(int delta) {
        m_mouseWheelDelta += delta;
    }

    int MouseInput::GetMouseWheelDeltaPickResult() {
        auto result{m_mouseWheelDelta};
        m_mouseWheelDelta = 0;
        return result;
    }
}