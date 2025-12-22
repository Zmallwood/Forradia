/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "MessageUtilities.hpp"
#include <iostream>

namespace Forradia
{
    auto Print(std::string_view text) -> void
    {
        std::cout << text;
    }

    auto PrintLine(std::string_view text) -> void
    {
        std::cout << text << std::endl;
    }
}
