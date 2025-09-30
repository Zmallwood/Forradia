/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia {
  class MouseButton {
  public:
    void Reset();

    void RegisterPress();

    void RegisterRelease();

    bool IsPressedPickResult();

    bool GetHasBeenFiredPickResult();

    bool GetHasBeenFiredDontPickResult();

    bool GetHasBeenReleasedPickResult();

    bool GetHasBeenReleasedDontPickResult();

  private:
    bool m_isPressed{false};
    bool m_hasBeenFired{false};
    bool m_hasBeenReleased{false};
  };
}