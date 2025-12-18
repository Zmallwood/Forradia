/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MouseButton.hpp"
#include "StdAfx.hpp"

namespace Forradia {
  auto MouseButton::HasBeenReleasedPickResult() -> bool {
    auto result{m_hasBeenReleased};
    m_hasBeenReleased = false;
    return result;
  }

  auto MouseButton::HasBeenReleased() const -> bool {
    return m_hasBeenReleased;
  }
}
