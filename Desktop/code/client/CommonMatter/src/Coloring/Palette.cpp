/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Palette.hpp"
#include "Hash.hpp"

namespace Forradia::Palette
{
    template <>
    auto GetColor<Hash("Black")>() -> Color
    {
        constexpr auto red{0.0F};
        constexpr auto green{0.0F};
        constexpr auto blue{0.0F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("White")>() -> Color
    {
        constexpr auto red{1.0F};
        constexpr auto green{1.0F};
        constexpr auto blue{1.0F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Wheat")>() -> Color
    {
        constexpr auto red{1.0F};
        constexpr auto green{1.0F};
        constexpr auto blue{0.65F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("WheatTransparent")>() -> Color
    {
        auto color{GetColor<Hash("Wheat")>()};

        constexpr auto alpha{0.7F};

        color.a = alpha;

        return color;
    }

    template <>
    auto GetColor<Hash("Yellow")>() -> Color
    {
        constexpr auto red{1.0F};
        constexpr auto green{1.0F};
        constexpr auto blue{0.0F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Gold")>() -> Color
    {
        constexpr auto red{1.0F};
        constexpr auto green{0.7F};
        constexpr auto blue{0.0F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("YellowTransparent")>() -> Color
    {
        auto color{GetColor<Hash("Yellow")>()};

        constexpr auto alpha{0.7F};

        color.a = alpha;

        return color;
    }

    template <>
    auto GetColor<Hash("MildBlue")>() -> Color
    {
        constexpr auto red{0.0F};
        constexpr auto green{0.4F};
        constexpr auto blue{1.0F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("MildBlueTransparent")>() -> Color
    {
        auto color{GetColor<Hash("MildBlue")>()};

        constexpr auto alpha{0.3F};

        color.a = alpha;

        return color;
    }

    template <>
    auto GetColor<Hash("LightBlue")>() -> Color
    {
        constexpr auto red{0.4F};
        constexpr auto green{0.4F};
        constexpr auto blue{1.0F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Red")>() -> Color
    {
        constexpr auto red{1.0F};
        constexpr auto green{0.0F};
        constexpr auto blue{0.0F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Green")>() -> Color
    {
        constexpr auto red{0.0F};
        constexpr auto green{1.0F};
        constexpr auto blue{0.0F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("DarkGreen")>() -> Color
    {
        constexpr auto red{0.2F};
        constexpr auto green{0.7F};
        constexpr auto blue{0.2F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Brown")>() -> Color
    {
        constexpr auto red{0.5F};
        constexpr auto green{0.25F};
        constexpr auto blue{0.0F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Gray")>() -> Color
    {
        constexpr auto red{0.5F};
        constexpr auto green{0.5F};
        constexpr auto blue{0.5F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("DarkGray")>() -> Color
    {
        constexpr auto red{0.3F};
        constexpr auto green{0.3F};
        constexpr auto blue{0.3F};
        constexpr auto alpha{1.0F};

        return {red, green, blue, alpha};
    }
}
