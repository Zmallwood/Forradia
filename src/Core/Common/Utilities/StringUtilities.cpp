/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "StringUtilities.hpp"

namespace Forradia
{
    String Replace(StringView text,
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
