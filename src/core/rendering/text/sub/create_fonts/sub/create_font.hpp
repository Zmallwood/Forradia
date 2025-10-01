/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "../../font_sizes.hpp"

namespace forr {
  s_ptr<TTF_Font> CreateFont(str_view fontFilePath, FontSizes fontSize);
}