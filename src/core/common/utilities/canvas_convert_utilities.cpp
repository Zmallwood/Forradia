/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "canvas_convert_utilities.hpp"
#include "canvas_utilities.hpp"

namespace forr {
  float ConvertWidthToHeight(float width) {
    return width * CalculateAspectRatio();
  }

  float ConvertHeightToWidth(float height) {
    return height / CalculateAspectRatio();
  }
}