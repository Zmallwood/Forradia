//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "MouseButton.hpp"

namespace Forradia {
bool MouseButton::HasBeenReleasedPickResult() {
  auto result{m_hasBeenReleased};
  m_hasBeenReleased = false;
  return result;
}

bool MouseButton::HasBeenReleased() const {
  return m_hasBeenReleased;
}
}