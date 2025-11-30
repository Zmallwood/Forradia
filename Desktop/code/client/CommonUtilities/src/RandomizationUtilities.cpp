//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "RandomizationUtilities.hpp"

namespace AAK
{
    namespace Forradia
    {
        void Randomize()
        {
            // Randomize the seed.

            srand(time(nullptr));
        }

        int GetRandomInt(int upperLimit)
        {
            // Generate a random integer.

            return rand() % upperLimit;
        }
    }
}