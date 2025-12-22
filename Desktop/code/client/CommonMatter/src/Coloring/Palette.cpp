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
        const auto red{0.0F};
        const auto green{0.0F};
        const auto blue{0.0F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("White")>() -> Color
    {
        const auto red{1.0F};
        const auto green{1.0F};
        const auto blue{1.0F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Wheat")>() -> Color
    {
        const auto red{1.0F};
        const auto green{1.0F};
        const auto blue{0.65F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("WheatTransparent")>() -> Color
    {
        auto color{GetColor<Hash("Wheat")>()};
        const auto alpha{0.7F};
        color.a = alpha;
        return color;
    }

    template <>
    auto GetColor<Hash("Yellow")>() -> Color
    {
        const auto red{1.0F};
        const auto green{1.0F};
        const auto blue{0.0F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Gold")>() -> Color
    {
        const auto red{1.0F};
        const auto green{0.7F};
        const auto blue{0.0F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("YellowTransparent")>() -> Color
    {
        auto color{GetColor<Hash("Yellow")>()};
        const auto alpha{0.7F};
        color.a = alpha;
        return color;
    }

    template <>
    auto GetColor<Hash("MildBlue")>() -> Color
    {
        const auto red{0.0F};
        const auto green{0.4F};
        const auto blue{1.0F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("LightBlue")>() -> Color
    {
        const auto red{0.4F};
        const auto green{0.4F};
        const auto blue{1.0F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Red")>() -> Color
    {
        const auto red{1.0F};
        const auto green{0.0F};
        const auto blue{0.0F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Green")>() -> Color
    {
        const auto red{0.0F};
        const auto green{1.0F};
        const auto blue{0.0F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Brown")>() -> Color
    {
        const auto red{0.5F};
        const auto green{0.25F};
        const auto blue{0.0F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("Gray")>() -> Color
    {
        const auto red{0.5F};
        const auto green{0.5F};
        const auto blue{0.5F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }

    template <>
    auto GetColor<Hash("DarkGray")>() -> Color
    {
        const auto red{0.3F};
        const auto green{0.3F};
        const auto blue{0.3F};
        const auto alpha{1.0F};

        return {red, green, blue, alpha};
    }
}
