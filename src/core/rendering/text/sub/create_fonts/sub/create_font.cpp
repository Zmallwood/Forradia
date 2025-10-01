/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_font.hpp"

namespace forr {
  s_ptr<TTF_Font> create_font(str_view fontFilePath, font_sizes fontSize) {
    auto fontPathUnixStyle{Replace(fontFilePath, '\\', '/')};
    auto fontSizeN{CInt(fontSize)};
    auto newFont{s_ptr<TTF_Font>(
        TTF_OpenFont(fontPathUnixStyle.c_str(), fontSizeN), sdl_deleter())};
    if (!newFont) {
      PrintLine("Error loading font.");
      return nullptr;
    }
    return newFont;
  }
}