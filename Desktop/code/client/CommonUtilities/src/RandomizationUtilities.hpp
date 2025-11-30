//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace AAK
{
    namespace Forradia
    {
        ///
        /// Randomize the seed.
        ///
        void Randomize();

        ///
        /// Generate a random integer.
        ///
        /// @param upperLimit Upper limit.
        /// @return Random integer.
        ///
        int GetRandomInt(int upperLimit);
    }
}