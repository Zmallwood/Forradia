/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "sub/font_sizes.hpp"

namespace forr {
  class TextRenderer {
  public:
    TextRenderer() { Initialize(); }

    void DrawString(str_view text, float x, float y,
                    FontSizes fontSize = FontSizes::_20,
                    bool centerAlign = false,
                    Color textColor = Colors::WheatTransparent) const;

  private:
    void Initialize();

    void AddFonts();

    void AddFontSize(FontSizes fontSize);

    const str k_defaultFontPath{"./Resources/Fonts/PixeloidSans.ttf"};

    std::map<FontSizes, s_ptr<TTF_Font>> m_fonts;
  };
}