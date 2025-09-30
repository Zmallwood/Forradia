/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "MeasureRenderedText.hpp"

namespace Forradia {
  Size MeasureRenderedText(StringView text, TTF_Font *fontRaw) {
    int textWidth;
    int textHeight;

    TTF_SizeText(fontRaw, text.data(), &textWidth, &textHeight);

    return {textWidth, textHeight};
  }
}