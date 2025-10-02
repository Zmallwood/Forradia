/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  enum class cursor_styles {
    normal,
    hovering_clickable_gui,
    hovering_creature
  };

  class cursor {
  public:
    cursor() { initialize(); }

    void reset_style_to_default();

    void render();

    auto set_cursor_style(cursor_styles value) { m_cursor_style = value; }

  private:
    void initialize();

    void disable_system_cursor();

    constexpr static float k_cursor_size{0.05f};

    cursor_styles m_cursor_style{cursor_styles::normal};
  };
}