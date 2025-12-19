/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "StringUtilities.hpp"

namespace Forradia {
  auto Replace(std::string_view text, char replace, char replaceWith) -> std::string {
    std::string result{text.data()};
    std::replace(result.begin(), result.end(), replace, replaceWith);
    return result;
  }
}
