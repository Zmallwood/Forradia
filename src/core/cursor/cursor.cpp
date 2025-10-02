/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "cursor.hpp"
#include "core/rendering/images/image_renderer.hpp"

namespace forr {
  void cursor::initialize() { disable_system_cursor(); }

  void cursor::disable_system_cursor() { SDL_ShowCursor(SDL_DISABLE); }

  void cursor::reset_style_to_default() {
    m_cursor_style = cursor_styles::normal;
  }

  void cursor::render() {
    auto mouse_position{get_normalized_mouse_position()};
    auto width{k_cursor_size};
    auto height{convert_width_to_height(k_cursor_size)};
    str cursor_image;
    switch (m_cursor_style) {
    case cursor_styles::normal:
      cursor_image = "CursorDefault";
      break;
    case cursor_styles::hovering_clickable_gui:
      cursor_image = "CursorHoveringClickableGUI";
      break;
    }
    get_singleton<image_renderer>().draw_image(
        cursor_image, mouse_position.x - width / 2,
        mouse_position.y - height / 2, width, height);
  }
}