/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Color.hpp"
#include "Constants.hpp"
#include <SDL2/SDL.h>

namespace Forradia
{
    auto Color::ToSDLColor() const -> SDL_Color
    {
        auto rUint{static_cast<Uint8>(r * k_maxColorComponentValue)};
        auto gUint{static_cast<Uint8>(g * k_maxColorComponentValue)};
        auto bUint{static_cast<Uint8>(b * k_maxColorComponentValue)};
        auto aUint{static_cast<Uint8>(a * k_maxColorComponentValue)};

        return {rUint, gUint, bUint, aUint};
    }
}
