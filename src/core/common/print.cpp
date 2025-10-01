/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "print.hpp"

namespace forr {
  void Print(str_view text) {
    // Print out text without a following line break.
    std::cout << text;
  }

  void PrintLine(str_view text) {
    // Print out text with a following line break.
    std::cout << text << std::endl;
  }
}