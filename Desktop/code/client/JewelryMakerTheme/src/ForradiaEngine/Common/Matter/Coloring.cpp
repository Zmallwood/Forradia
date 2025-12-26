/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
#include "Coloring.hpp"
#include "ForradiaEngine/Common/General/Constants.hpp"
#include "ForradiaEngine/Common/Utilities/ErrorUtilities.hpp"
#include <SDL2/SDL.h>
// clang-format on

namespace ForradiaEngine
{
    auto Color::toSDLColor() const -> SDL_Color
    {
        /* Validation */ // clang-format off
            throwOnFalse(r >= 0.0F && r <= 1.0F, "r is out of range");
            throwOnFalse(g >= 0.0F && g <= 1.0F, "g is out of range");
            throwOnFalse(b >= 0.0F && b <= 1.0F, "b is out of range");
            throwOnFalse(a >= 0.0F && a <= 1.0F, "a is out of range");
        // clang-format on */

        /* Calculations */ // clang-format off
            auto rUint{static_cast<Uint8>(r * k_maxColorComponentValue)};
            auto gUint{static_cast<Uint8>(g * k_maxColorComponentValue)};
            auto bUint{static_cast<Uint8>(b * k_maxColorComponentValue)};
            auto aUint{static_cast<Uint8>(a * k_maxColorComponentValue)};
        // clang-format on */

        return {rUint, gUint, bUint, aUint};
    }

    /* Palette */ // clang-format off
        namespace Palette
        {
            template <>
            auto getColor<hash("Black")>() -> Color
            {
                constexpr auto red{0.0F};
                constexpr auto green{0.0F};
                constexpr auto blue{0.0F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("White")>() -> Color
            {
                constexpr auto red{1.0F};
                constexpr auto green{1.0F};
                constexpr auto blue{1.0F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("Wheat")>() -> Color
            {
                constexpr auto red{1.0F};
                constexpr auto green{1.0F};
                constexpr auto blue{0.65F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("WheatTransparent")>() -> Color
            {
                auto color{getColor<hash("Wheat")>()};

                constexpr auto alpha{0.7F};

                color.a = alpha;

                return color;
            }

            template <>
            auto getColor<hash("Yellow")>() -> Color
            {
                constexpr auto red{1.0F};
                constexpr auto green{1.0F};
                constexpr auto blue{0.0F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("Gold")>() -> Color
            {
                constexpr auto red{1.0F};
                constexpr auto green{0.7F};
                constexpr auto blue{0.0F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("YellowTransparent")>() -> Color
            {
                auto color{getColor<hash("Yellow")>()};

                constexpr auto alpha{0.7F};

                color.a = alpha;

                return color;
            }

            template <>
            auto getColor<hash("MildBlue")>() -> Color
            {
                constexpr auto red{0.0F};
                constexpr auto green{0.4F};
                constexpr auto blue{1.0F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("MildBlueTransparent")>() -> Color
            {
                auto color{getColor<hash("MildBlue")>()};

                constexpr auto alpha{0.3F};

                color.a = alpha;

                return color;
            }

            template <>
            auto getColor<hash("LightBlue")>() -> Color
            {
                constexpr auto red{0.4F};
                constexpr auto green{0.4F};
                constexpr auto blue{1.0F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("Red")>() -> Color
            {
                constexpr auto red{1.0F};
                constexpr auto green{0.0F};
                constexpr auto blue{0.0F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("Green")>() -> Color
            {
                constexpr auto red{0.0F};
                constexpr auto green{1.0F};
                constexpr auto blue{0.0F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("DarkGreen")>() -> Color
            {
                constexpr auto red{0.2F};
                constexpr auto green{0.7F};
                constexpr auto blue{0.2F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("Brown")>() -> Color
            {
                constexpr auto red{0.5F};
                constexpr auto green{0.25F};
                constexpr auto blue{0.0F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("Gray")>() -> Color
            {
                constexpr auto red{0.5F};
                constexpr auto green{0.5F};
                constexpr auto blue{0.5F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }

            template <>
            auto getColor<hash("DarkGray")>() -> Color
            {
                constexpr auto red{0.3F};
                constexpr auto green{0.3F};
                constexpr auto blue{0.3F};
                constexpr auto alpha{1.0F};

                return {red, green, blue, alpha};
            }
        }
    // clang-format on
}
