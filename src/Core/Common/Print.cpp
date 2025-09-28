/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Print.hpp"

namespace Forradia
{
    void Print(StringView text)
    {
        std::cout << text;
    }

    void PrintLine(StringView text)
    {
        std::cout << text << std::endl;
    }
}