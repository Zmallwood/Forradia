/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "RandomizationUtilities.hpp"
#include <cstdlib>
#include <ctime>

namespace Forradia {
    auto Randomize() -> void {
        srand(time(nullptr));
    }

    auto GetRandomInt(int upperLimit) -> int {
        return rand() % upperLimit;
    }
}
