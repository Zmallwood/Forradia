/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "gui_panel.hpp"

namespace forr {
  class GUITextConsole : public GUIPanel {
  public:
    GUITextConsole()
        : GUIPanel(0.0f, 0.8f, 0.4f, 0.2f, k_defaultBackgroundImageDerived) {}

    void RenderDerived() const override;

    void Print(StringView text);

  private:
    constexpr static StringView k_defaultBackgroundImageDerived{
        "GUITextConsoleBackground"};
    inline static const float k_lineHeight{0.025f};
    inline static const float k_separatorHeight{0.003f};
    inline static const float k_margin{0.008f};

    Vector<String> m_textLines;
  };
}