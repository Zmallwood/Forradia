/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    /**
     * Gets the name from a hash code as a template function, i.e. it reverses the Hash function.
     *
     * @param N The hash code to get the name from.
     * @return The name from the hash code.
     */
    template <int N>
    auto GetNameFromHash() -> std::string;

    /**
     * Gets the name from a hash code, i.e. it reverses the Hash function.
     *
     * @param hash The hash code to get the name from.
     * @return The name from the hash code.
     */
    auto GetNameFromAnyHash(int hash) -> std::string;
}
