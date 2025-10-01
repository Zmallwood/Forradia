/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "../font_sizes.hpp"

namespace forr {
  std::map<FontSizes, s_ptr<TTF_Font>> CreateFonts(vec<FontSizes> fontSizes,
                                                  str_view relativeFontPath);
}