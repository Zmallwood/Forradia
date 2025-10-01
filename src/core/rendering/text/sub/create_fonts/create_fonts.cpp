/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_fonts.hpp"
#include "sub/create_font.hpp"

namespace forr {
  std::map<FontSizes, s_ptr<TTF_Font>> CreateFonts(vec<FontSizes> fontSizes,
                                                  str_view relativeFontPath) {
    std::map<FontSizes, s_ptr<TTF_Font>> fontsResult;
    auto absoluteFontPath{str(SDL_GetBasePath()) + relativeFontPath.data()};
    for (auto fontSize : fontSizes) {
      auto newFont{CreateFont(absoluteFontPath, fontSize)};
      fontsResult.insert({fontSize, newFont});
    }
    return fontsResult;
  }
}