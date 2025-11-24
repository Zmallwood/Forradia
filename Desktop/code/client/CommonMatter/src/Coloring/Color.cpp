//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Color.hpp"

#include "Functions.hpp"

namespace Forradia
{
    SDL_Color Color::ToSDLColor() const
    {
        // Calculate individual color components.

        // Red.

        auto rUint{CUint8(r * 255)};

        // Green.

        auto gUint{CUint8(g * 255)};

        // Blue.

        auto bUint{CUint8(b * 255)};

        // Alpha.

        auto aUint{CUint8(a * 255)};

        // Return the SDL_Color object.

        return {rUint, rUint, bUint, aUint};
    }
}