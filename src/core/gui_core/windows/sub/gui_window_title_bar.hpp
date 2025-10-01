/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

namespace forr {
  class gui_window;

  class gui_window_title_bar {
  public:
    gui_window_title_bar(gui_window &parentWindow, str_view windowTitleText)
        : m_parentWindow(parentWindow), k_windowTitleText(windowTitleText) {}

    void render() const;

    rect_f get_bounds() const;

  private:
    inline static const float k_height{0.04f};
    const str k_windowTitleText;

    gui_window &m_parentWindow;
  };
}