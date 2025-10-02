/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once
#include "../../font_sizes.hpp"

namespace forr {
  s_ptr<TTF_Font> create_font(str_view font_file_path, font_sizes font_size);
}