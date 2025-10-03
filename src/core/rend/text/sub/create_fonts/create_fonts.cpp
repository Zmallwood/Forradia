/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_fonts.hpp"
#include "sub/create_font.hpp"

namespace forr {
  std::map<font_sizes, s_ptr<TTF_Font>> create_fonts(vec<font_sizes> font_szs,
                                                     str_view rel_font_path) {
    std::map<forr::font_sizes, s_ptr<TTF_Font>> fonts_res;
    auto abs_font_path{str(SDL_GetBasePath()) + rel_font_path.data()};
    for (auto font_sz : font_szs) {
      auto new_font{create_font(abs_font_path, font_sz)};
      fonts_res.insert({font_sz, new_font});
    }
    return fonts_res;
  }
}