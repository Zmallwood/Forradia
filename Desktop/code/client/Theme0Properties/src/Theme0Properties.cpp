/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Theme0Properties.hpp"
#include "StdAfx.hpp"

namespace Forradia::Theme0 {
auto Theme0Properties::GetGameWindowTitle() const -> String {
  return "Forradia";
}

auto Theme0Properties::GetClearColor() const -> Color {
  return Palette::GetColor<Hash("MildBlue")>();
}

auto Theme0Properties::GetGridSize() const -> Size {
  return {45, 45};
}

auto Theme0Properties::GetBaseWorldAreaSize() const -> Size {
  return {120, 100};
}

auto Theme0Properties::GetWorldScaling() const -> float {
  return 5.0f;
}

auto Theme0Properties::GetTileSize() const -> float {
  return 1.6f;
}

auto Theme0Properties::GetElevationHeight() const -> float {
  return 0.15f;
}
}
