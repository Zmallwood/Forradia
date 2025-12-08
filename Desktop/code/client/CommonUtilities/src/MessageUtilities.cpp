//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "MessageUtilities.hpp"

namespace Forradia
{
    void Print(StringView text)
    {
        // Print out text without a following line break.
        std::cout << text;
    }

    void PrintLine(StringView text)
    {
        // Print out text with a following line break.
        std::cout << text << std::endl;
    }
}