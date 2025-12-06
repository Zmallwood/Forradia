//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// TODO:
// Nothing

#include "Color.hpp"
#include "Functions.hpp"

namespace Forradia
{
    SDL_Color Color::ToSDLColor() const
    {
        // Calculate individual color components.

        auto rUint{CUint8(r * 255)};

        auto gUint{CUint8(g * 255)};

        auto bUint{CUint8(b * 255)};

        auto aUint{CUint8(a * 255)};

        return {rUint, rUint, bUint, aUint};
    }
}