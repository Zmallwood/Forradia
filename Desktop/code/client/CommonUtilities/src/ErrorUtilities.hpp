/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <source_location>
#include <string_view>

namespace Forradia
{
    [[noreturn]] void ThrowError(std::string_view message,
                                 std::source_location loc = std::source_location::current());
}
