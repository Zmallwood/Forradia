/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MouseButton.hpp"

namespace Forradia {
void MouseButton::Reset() {
  m_pressed = false;
  m_hasBeenFired = false;
  m_hasBeenReleased = false;
}

void MouseButton::RegisterPress() {
  m_pressed = true;
  m_hasBeenFired = true;
  m_ticksFired = GetTicks();
}

void MouseButton::RegisterRelease() {
  m_pressed = false;
  m_hasBeenReleased = true;
  m_ticksClickSpeed = GetTicks() - m_ticksFired;
}

bool MouseButton::IsPressedPickResult() {
  auto result{m_pressed};
  m_pressed = false;
  return result;
}
}