/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "../font_sizes.hpp"

namespace forr {
  std::map<font_sizes, s_ptr<TTF_Font>> create_fonts(vec<font_sizes> font_szs,
                                                     str_view rel_font_path);
}