#include "Color.hpp"

namespace Forradia
{
    SDL_Color Color::ToSDLColor() const
    {
        auto rInt{static_cast<Uint8>(r * 255)};
        auto gInt{static_cast<Uint8>(g * 255)};
        auto bInt{static_cast<Uint8>(b * 255)};
        auto aInt{static_cast<Uint8>(a * 255)};

        return {rInt, gInt, bInt, aInt};
    }
}