/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#include "string_utilities.hpp"

namespace forr {
  String Replace(StringView text, char replaced, char replacedWith) {
    String textData{text.data()};
    std::replace(textData.begin(), textData.end(), replaced, replacedWith);
    return textData;
  }
}
