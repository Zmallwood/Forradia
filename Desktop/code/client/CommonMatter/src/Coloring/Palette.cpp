/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Palette.hpp"
#include "Hash.hpp"

namespace Forradia::Palette
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
