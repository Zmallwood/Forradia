/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_panel.hpp"

namespace forr {
  class gui_text_console : public gui_panel {
  public:
    gui_text_console()
        : gui_panel(0.0f, 0.8f, 0.4f, 0.2f, k_defaultBackgroundImageDerived) {}

    void RenderDerived() const override;

    void Print(str_view text);

  private:
    constexpr static str_view k_defaultBackgroundImageDerived{
        "GUITextConsoleBackground"};
    inline static const float k_lineHeight{0.025f};
    inline static const float k_separatorHeight{0.003f};
    inline static const float k_margin{0.008f};

    vec<str> m_textLines;
  };
}