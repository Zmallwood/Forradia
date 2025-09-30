/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "MouseButton.hpp"

namespace Forradia {
  class MouseInput {
  public:
    void Reset();

    void RegisterMouseButtonDown(Uint8 mouseButton);

    void RegisterMouseButtonUp(Uint8 mouseButton);

    bool AnyMouseButtonIsPressedPickResult();

    auto &GetLeftMouseButtonRef() { return m_leftMouseButton; }

    auto &GetRightMouseButtonRef() { return m_leftMouseButton; }

  private:
    MouseButton m_leftMouseButton;
    MouseButton m_rightMouseButton;
  };
}