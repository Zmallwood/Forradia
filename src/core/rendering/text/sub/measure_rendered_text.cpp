/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "measure_rendered_text.hpp"

namespace forr {
  size measure_rendered_text(str_view text, TTF_Font *fontRaw) {
    int textWidth;
    int textHeight;
    TTF_SizeText(fontRaw, text.data(), &textWidth, &textHeight);
    return {textWidth, textHeight};
  }
}