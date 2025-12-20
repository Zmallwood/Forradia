/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include <string_view>

namespace Forradia {
  /**
   * Compute hash code from a given input text, which gets computed the same every game
   * start.
   *
   * @param text Text to compute hash code for.
   * @return Computed hash code.
   */
  constexpr auto Hash(std::string_view text) -> int {
    // Use djb2 algorithm by Daniel J. Bernstein.
    const unsigned long algorithmConstant{5381};
    const unsigned long algorithmFactor{33};
    unsigned long hash{algorithmConstant};
    for (char chr : text)
      hash = algorithmFactor * hash + (unsigned char)chr;
    return static_cast<int>(hash);
  }
}
