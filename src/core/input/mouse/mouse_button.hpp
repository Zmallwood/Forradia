/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class mouse_button {
  public:
    void reset();

    void register_press();

    void register_release();

    bool is_pressed_pick_result();

    bool get_has_been_fired_pick_result();

    bool get_has_been_fired_dont_pick_result();

    bool get_has_been_released_pick_result();

    bool get_has_been_released_dont_pick_result();

  private:
    bool m_isPressed{false};
    bool m_hasBeenFired{false};
    bool m_hasBeenReleased{false};
  };
}