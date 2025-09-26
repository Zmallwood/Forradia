/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "StringUtilities.hpp"

namespace Forradia
{
    std::string Replace(std::string_view text,
                        char replaced,
                        char replacedWith)
    {
        std::string textData{text.data()};

        std::replace(
            textData.begin(),
            textData.end(),
            replaced,
            replacedWith);

        return textData;
    }
}
