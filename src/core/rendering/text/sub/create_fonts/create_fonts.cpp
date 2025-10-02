/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_fonts.hpp"
#include "sub/create_font.hpp"

namespace forr {
  std::map<font_sizes, s_ptr<TTF_Font>>
  create_fonts(vec<font_sizes> font_sizes, str_view relative_font_path) {
    std::map<forr::font_sizes, s_ptr<TTF_Font>> fonts_result;
    auto absolute_font_path{str(SDL_GetBasePath()) + relative_font_path.data()};
    for (auto font_size : font_sizes) {
      auto new_font{create_font(absolute_font_path, font_size)};
      fonts_result.insert({font_size, new_font});
    }
    return fonts_result;
  }
}