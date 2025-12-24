/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Color.hpp"
#include "Common/General/Constants.hpp"
#include "Common/Utilities/ErrorUtilities.hpp"
#include <SDL2/SDL.h>

namespace Forradia
{
    auto Color::toSDLColor() const -> SDL_Color
    {
        { // Validation
            throwOnFalse(r >= 0.0F && r <= 1.0F, "r is out of range");
            throwOnFalse(g >= 0.0F && g <= 1.0F, "g is out of range");
            throwOnFalse(b >= 0.0F && b <= 1.0F, "b is out of range");
            throwOnFalse(a >= 0.0F && a <= 1.0F, "a is out of range");
        }

        auto rUint{static_cast<Uint8>(r * k_maxColorComponentValue)};
        auto gUint{static_cast<Uint8>(g * k_maxColorComponentValue)};
        auto bUint{static_cast<Uint8>(b * k_maxColorComponentValue)};
        auto aUint{static_cast<Uint8>(a * k_maxColorComponentValue)};

        return {rUint, gUint, bUint, aUint};
    }
}
