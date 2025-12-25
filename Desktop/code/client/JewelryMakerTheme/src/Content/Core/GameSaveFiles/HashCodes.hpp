/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <string>
// clang-format on

namespace Forradia::Theme0
{
    /**
     *  Gets the name from a hash code as a template function, i.e. it reverses the Hash function.
     *
     *  @tparam N The hash code to get the name from.
     *  @return The name from the hash code.
     */
    template <int N>
    // ReSharper disable once CppFunctionIsNotImplemented
    auto getNameFromHash() -> std::string;

    /**
     *  Gets the name from a hash code, i.e. it reverses the Hash function.
     *
     *  @param hashCode The hash code to get the name from.
     *  @return The name from the hash code.
     */
    auto getNameFromAnyHash(int hashCode) -> std::string;
}
