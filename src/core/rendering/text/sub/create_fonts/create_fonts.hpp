/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "../font_sizes.hpp"

namespace Forradia {
  Map<FontSizes, SharedPtr<TTF_Font>> CreateFonts(Vector<FontSizes> fontSizes,
                                                  StringView relativeFontPath);
}