/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "../font_sizes.hpp"

namespace forr {
  std::map<font_sizes, s_ptr<TTF_Font>> CreateFonts(vec<font_sizes> fontSizes,
                                                    str_view relativeFontPath);
}