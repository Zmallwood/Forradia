/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <source_location>
#include <string_view>

namespace Forradia
{
    /**
     *  Throw an error with a given message.
     *
     *  @param message The message to throw.
     *  @param loc The source location of the error, should not be provided manually.
     */
    [[noreturn]] void throwError(std::string_view message,
                                 std::source_location loc = std::source_location::current());

    /**
     *  Throw an error if a condition is false.
     *
     *  @param condition The condition to check.
     *  @param message The message to throw.
     *  @param loc The source location of the error, should not be provided manually.
     */
    void throwOnFalse(bool condition, std::string_view message,
                      std::source_location loc = std::source_location::current());
}
