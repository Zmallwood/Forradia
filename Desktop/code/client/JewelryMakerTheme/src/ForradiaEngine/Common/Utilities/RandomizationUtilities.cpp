/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "RandomizationUtilities.hpp"
    #include <cstdlib>
    #include <ctime>
// clang-format on

namespace Forradia
{
    auto randomize() -> void
    {
        srand(time(nullptr));
    }

    auto getRandomInt(int upperLimit) -> int
    {
        return rand() % upperLimit;
    }
}
