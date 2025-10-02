/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_font.hpp"

namespace forr {
  s_ptr<TTF_Font> create_font(str_view font_file_path, font_sizes font_size) {
    auto font_path_unix_style{replace(font_file_path, '\\', '/')};
    auto font_size_n{c_int(font_size)};
    auto new_font{
        s_ptr<TTF_Font>(TTF_OpenFont(font_path_unix_style.c_str(), font_size_n),
                        sdl_deleter())};
    if (!new_font) {
      print_line("Error loading font.");
      return nullptr;
    }
    return new_font;
  }
}