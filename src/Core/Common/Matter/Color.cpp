/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "Color.hpp"

namespace Forradia
{
    SDL_Color Color::ToSDLColor() const
    {
        auto rInt{CUint8(r * 255)};
        auto gInt{CUint8(g * 255)};
        auto bInt{CUint8(b * 255)};
        auto aInt{CUint8(a * 255)};

        return {rInt, gInt, bInt, aInt};
    }
}