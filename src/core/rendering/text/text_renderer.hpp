/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "sub/font_sizes.hpp"

namespace forr {
  class text_renderer {
  public:
    text_renderer() { Initialize(); }

    void DrawString(str_view text, float x, float y,
                    font_sizes fontSize = font_sizes::_20,
                    bool centerAlign = false,
                    color textColor = colors::WheatTransparent) const;

  private:
    void Initialize();

    void AddFonts();

    void AddFontSize(font_sizes fontSize);

    const str k_defaultFontPath{"./Resources/Fonts/PixeloidSans.ttf"};

    std::map<font_sizes, s_ptr<TTF_Font>> m_fonts;
  };
}