/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MouseInput.hpp"

namespace Forradia {
  auto MouseInput::Reset() -> void {
    m_leftMouseButton.Reset();
    m_rightMouseButton.Reset();
  }

  auto MouseInput::AnyMouseButtonIsPressedPickResult() -> bool {
    auto result{m_leftMouseButton.IsPressedPickResult()};
    result |= m_rightMouseButton.IsPressedPickResult();
    return result;
  }

  auto MouseInput::AddMouseWheelDelta(int delta) -> void {
    m_mouseWheelDelta += delta;
  }

  auto MouseInput::GetMouseWheelDeltaPickResult() -> int {
    auto result{m_mouseWheelDelta};
    m_mouseWheelDelta = 0;
    return result;
  }
}
