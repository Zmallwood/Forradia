/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "sub/font_sizes.hpp"

namespace forr {
  class text_renderer {
   public:
    text_renderer() { initialize(); }

    void draw_string(str_view text, float x, float y,
                     font_sizes font_sz = font_sizes::_20,
                     bool cent_align = false,
                     color text_color = colors::wheat_transp) const;

   private:
    void initialize();

    void add_fonts();

    const str k_default_font_path{"./Resources/Fonts/PixeloidSans.ttf"};

    std::map<font_sizes, s_ptr<TTF_Font>> m_fonts;
  };
}