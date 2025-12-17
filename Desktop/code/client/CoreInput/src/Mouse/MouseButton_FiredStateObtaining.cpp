/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MouseButton.hpp"
#include "StdAfx.hpp"

namespace Forradia {
auto MouseButton::HasBeenFiredPickResult() -> bool {
  auto result{m_hasBeenFired};
  m_hasBeenFired = false;
  return result;
}

auto MouseButton::HasBeenFired() const -> bool {
  return m_hasBeenFired;
}
}
