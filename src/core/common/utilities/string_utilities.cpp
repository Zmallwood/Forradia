/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "string_utilities.hpp"

namespace forr {
  str Replace(str_view text, char replaced, char replacedWith) {
    str textData{text.data()};
    std::replace(textData.begin(), textData.end(), replaced, replacedWith);
    return textData;
  }
}
