/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace forr {
  enum struct font_sizes { _20 = 20, _26 = 26 };

  class text_renderer {
   public:
    text_renderer() { init(); }

    void draw_str(str_view text, float x, float y,
                  font_sizes font_sz = font_sizes::_20, bool cent_align = false,
                  color text_color = colors::wheat_transp) const;

   private:
    void init();

    void add_fonts();

    const str k_default_font_path{"./Resources/Fonts/PixeloidSans.ttf"};

    std::map<font_sizes, s_ptr<TTF_Font>> m_fonts;
  };
}