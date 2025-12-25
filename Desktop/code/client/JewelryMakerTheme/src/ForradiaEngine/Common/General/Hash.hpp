/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/Common/Utilities/ErrorUtilities.hpp"
    #include <string_view>
// clang-format on

namespace ForradiaEngine
{
    /**
     * Compute hash code from a given input text, which gets computed the same every game
     * start.
     * @param text Text to compute hash code for.
     * @return Computed hash code.
     */
    constexpr auto hash(std::string_view text) -> int
    {
        // Use djb2 algorithm by Daniel J. Bernstein.
        constexpr unsigned long algorithmConstant{5381};

        unsigned long hash{algorithmConstant};

        for (char chr : text)
        {
            constexpr unsigned long algorithmFactor{33};

            hash = algorithmFactor * hash + static_cast<unsigned char>(chr);
        }

        return static_cast<int>(hash);
    }
}
