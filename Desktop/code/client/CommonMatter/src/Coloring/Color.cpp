/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Color.hpp"
#include "Constants.hpp"
#include "Functions.hpp"
#include "StdAfx.hpp"

namespace Forradia {
auto Color::ToSDLColor() const -> SDL_Color {
  auto rUint{CUint8(r * k_maxColorComponentValue)};
  auto gUint{CUint8(g * k_maxColorComponentValue)};
  auto bUint{CUint8(b * k_maxColorComponentValue)};
  auto aUint{CUint8(a * k_maxColorComponentValue)};
  return {rUint, gUint, bUint, aUint};
}
}
