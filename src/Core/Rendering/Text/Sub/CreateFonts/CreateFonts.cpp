/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CreateFonts.hpp"
#include "Sub/CreateFont.hpp"

namespace Forradia {
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