/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "MessageUtilities.hpp"

namespace Forradia {
  auto Print(StringView text) -> void {
    std::cout << text;
  }

  auto PrintLine(StringView text) -> void {
    std::cout << text << std::endl;
  }
}
