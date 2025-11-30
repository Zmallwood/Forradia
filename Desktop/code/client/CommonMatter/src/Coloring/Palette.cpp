//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Palette.hpp"

#include "Hash.hpp"

namespace AAK
{
    namespace Forradia::Palette
    {
        // Define a palette of colors for the application.

        template <>
        Color GetColor<Hash("Black")>()
        {
            return {0.0f, 0.0f, 0.0f, 1.0f};
        }

        template <>
        Color GetColor<Hash("Wheat")>()
        {
            return {1.0f, 1.0f, 0.65f, 1.0f};
        }

        template <>
        Color GetColor<Hash("WheatTransparent")>()
        {
            // Use existing wheat color and just change the alpha.

            auto color{GetColor<Hash("Wheat")>()};

            color.a = 0.7f;

            return color;
        }

        template <>
        Color GetColor<Hash("Yellow")>()
        {
            return {1.0f, 1.0f, 0.0f, 1.0f};
        }

        template <>
        Color GetColor<Hash("YellowTransparent")>()
        {
            // Use existing yellow color and just change the alpha.

            auto color{GetColor<Hash("Yellow")>()};

            color.a = 0.7f;

            return color;
        }

        template <>
        Color GetColor<Hash("MildBlue")>()
        {
            return {0.0f, 0.4f, 0.9f, 1.0f};
        }

        template <>
        Color GetColor<Hash("Red")>()
        {
            return {1.0f, 0.0f, 0.0f, 1.0f};
        }
    }
}