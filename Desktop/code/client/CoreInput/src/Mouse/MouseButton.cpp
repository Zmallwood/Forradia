/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MouseButton.hpp"
#include "StdAfx.hpp"

namespace Forradia {
auto MouseButton::Reset() -> void {
  m_pressed = false;
  m_hasBeenFired = false;
  m_hasBeenReleased = false;
}

auto MouseButton::RegisterPress() -> void {
  m_pressed = true;
  m_hasBeenFired = true;
  m_ticksFired = GetTicks();
}

auto MouseButton::RegisterRelease() -> void {
  m_pressed = false;
  m_hasBeenReleased = true;
  m_ticksClickSpeed = GetTicks() - m_ticksFired;
}

auto MouseButton::IsPressedPickResult() -> bool {
  auto result{m_pressed};
  m_pressed = false;
  return result;
}
}
