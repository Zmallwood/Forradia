/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "NumbersUtilities.hpp"
#include "Constants.hpp"

namespace Forradia {
auto InvertSpeed(float speed) -> float {
  if (speed) {
    return k_oneSecMillis / speed;
  } else {
    return 0.0f;
  }
}

auto Normalize(int value) -> int {
  auto absValue{std::abs(value)};
  auto normalized{0};
  if (value) {
    normalized = value / absValue;
  }
  return normalized;
}

auto Ceil(float number, float numDecimalPlaces) -> float {
  auto p{std::pow(10.0, numDecimalPlaces)};
  return std::ceil(number * p) / p;
}
}