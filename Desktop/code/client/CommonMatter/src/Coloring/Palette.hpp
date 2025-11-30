//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Coloring/Color.hpp"

namespace AAK
{
    namespace Forradia::Palette
    {
        ///
        /// Get a color from the palette.
        ///
        /// @param N The hash of the name of the color to get.
        /// @return The color.
        ///
        template <int N>
        Color GetColor();
    }
}