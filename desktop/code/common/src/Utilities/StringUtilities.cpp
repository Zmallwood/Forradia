//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "StringUtilities.hpp"

namespace Forradia
{
    String Replace(StringView text, char replace,
                   char replaceWith)
    {
        // Create a copy of the string.

        String result{text.data()};

        // Replace all instances of repl with repl_with.

        std::replace(result.begin(), result.end(), replace,
                     replaceWith);

        return result;
    }
}