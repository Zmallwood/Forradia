/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "create_fonts.hpp"
#include "sub/create_font.hpp"

namespace forr {
  Map<FontSizes, SharedPtr<TTF_Font>> CreateFonts(Vector<FontSizes> fontSizes,
                                                  StringView relativeFontPath) {
    Map<FontSizes, SharedPtr<TTF_Font>> fontsResult;
    auto absoluteFontPath{String(SDL_GetBasePath()) + relativeFontPath.data()};
    for (auto fontSize : fontSizes) {
      auto newFont{CreateFont(absoluteFontPath, fontSize)};
      fontsResult.insert({fontSize, newFont});
    }
    return fontsResult;
  }
}