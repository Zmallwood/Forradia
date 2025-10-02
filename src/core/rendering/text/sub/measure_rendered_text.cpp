/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "measure_rendered_text.hpp"

namespace forr {
  size measure_rendered_text(str_view text, TTF_Font *font_raw) {
    int text_width;
    int text_height;
    TTF_SizeText(font_raw, text.data(), &text_width, &text_height);
    return {text_width, text_height};
  }
}