//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once
#include "Aliases.hpp"
#include "Functions.hpp"

namespace Forradia {
/// Compute hash code from a given input text, which gets computed the same every game
/// start.
///
/// @param text Text to compute hash code for.
/// @return Computed hash code.
constexpr int Hash(StringView text) {
  // Use djb2 algorithm by Daniel J. Bernstein.
  unsigned long hash{5381};
  for (size_t i = 0; i < text.size(); ++i) {
    hash = 33 * hash + (unsigned char)text[i];
  }
  return CInt(hash);
}
}