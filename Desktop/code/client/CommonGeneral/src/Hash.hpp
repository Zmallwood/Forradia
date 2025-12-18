/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "Aliases.hpp"
#include "Functions.hpp"

namespace Forradia {
  /**
   * Compute hash code from a given input text, which gets computed the same every game
   * start.
   *
   * @param text Text to compute hash code for.
   * @return Computed hash code.
   */
  constexpr auto Hash(StringView text) -> int {
    // Use djb2 algorithm by Daniel J. Bernstein.
    const unsigned long algorithmConstant{5381};
    const unsigned long algorithmMultiplier{33};
    unsigned long hash{algorithmConstant};
    for (char chr : text)
      hash = algorithmMultiplier * hash + (unsigned char)chr;
    return CInt(hash);
  }
}
