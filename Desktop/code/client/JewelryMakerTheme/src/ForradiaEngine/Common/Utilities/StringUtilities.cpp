/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "StringUtilities.hpp"
    #include <algorithm>
// clang-format on

namespace ForradiaEngine
{
    auto replace(std::string_view text, char replace, char replaceWith) -> std::string
    {
        std::string result{text.data()};

        std::replace(result.begin(), result.end(), replace, replaceWith);

        return result;
    }
}
