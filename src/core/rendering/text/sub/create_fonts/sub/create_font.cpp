/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_font.hpp"

namespace forr {
  s_ptr<TTF_Font> CreateFont(str_view fontFilePath, FontSizes fontSize) {
    auto fontPathUnixStyle{Replace(fontFilePath, '\\', '/')};
    auto fontSizeN{CInt(fontSize)};
    auto newFont{s_ptr<TTF_Font>(
        TTF_OpenFont(fontPathUnixStyle.c_str(), fontSizeN), SDLDeleter())};
    if (!newFont) {
      PrintLine("Error loading font.");
      return nullptr;
    }
    return newFont;
  }
}