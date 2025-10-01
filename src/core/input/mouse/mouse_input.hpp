/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "mouse_button.hpp"

namespace forr {
  class mouse_input {
  public:
    void Reset();

    void RegisterMouseButtonDown(Uint8 mouseButton);

    void RegisterMouseButtonUp(Uint8 mouseButton);

    bool AnyMouseButtonIsPressedPickResult();

    auto &GetLeftMouseButtonRef() { return m_leftMouseButton; }

    auto &GetRightMouseButtonRef() { return m_leftMouseButton; }

  private:
    mouse_button m_leftMouseButton;
    mouse_button m_rightMouseButton;
  };
}