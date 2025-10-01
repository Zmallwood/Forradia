/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "hash.hpp"

namespace forr {
  int Hash(StringView text) {
    // Use algorithm from forgotten source.
    unsigned long hash{5381};
    for (size_t i = 0; i < text.size(); ++i) {
      hash = 33 * hash + (unsigned char)text[i];
    }
    return CInt(hash);
  }
}
