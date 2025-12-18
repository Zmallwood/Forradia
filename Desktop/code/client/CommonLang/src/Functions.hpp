/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include <SDL2/SDL.h>

using Uint8 = uint8_t;

namespace Forradia {
  /**
   * Can be used to cast any value to int.
   *
   * @param value Value to cast.
   * @return Casted value.
   */
  constexpr auto CInt(auto value) -> int {
    return static_cast<int>(value);
  }

  /**
   * Can be used to cast any value to float.
   *
   * @param value Value to cast.
   * @return Casted value.
   */
  constexpr auto CFloat(auto value) -> float {
    return static_cast<float>(value);
  }

  /**
   * Can be used to cast any value to Uint8.
   *
   * @param value Value to cast.
   * @return Casted value.
   */
  constexpr auto CUint8(auto value) -> Uint8 {
    return static_cast<Uint8>(value);
  }
}
