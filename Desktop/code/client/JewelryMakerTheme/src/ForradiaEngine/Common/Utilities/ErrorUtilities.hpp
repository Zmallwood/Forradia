/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <source_location>
    #include <string_view>
// clang-format on

namespace ForradiaEngine
{
    /**
     *  Throw an error with a given message.
     *
     *  @param message The message to throw.
     *  @param loc The source location of the error, should not be provided manually.
     */
    [[noreturn]] auto throwError(std::string_view message,
                                 std::source_location loc = std::source_location::current())
        -> void;

    /**
     *  Throw an error if a condition is false.
     *
     *  @param condition The condition to check.
     *  @param message The message to throw.
     *  @param loc The source location of the error, should not be provided manually.
     */
    auto throwOnFalse(bool condition, std::string_view message,
                      std::source_location loc = std::source_location::current()) -> void;
}
