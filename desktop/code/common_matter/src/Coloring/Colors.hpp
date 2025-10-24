//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Color.hpp"

namespace Forradia
{
    ///
    /// Contains a palette of colors.
    ///
    namespace Colors
    {
        constexpr Color Black{0.0f, 0.0f, 0.0f,
                              1.0f}; ///< Black color.

        constexpr Color Wheat{1.0f, 1.0f, 0.65f,
                              1.0f}; ///< Wheat color.

        constexpr Color WheatTransparent{
            1.0f, 1.0f, 0.65f,
            0.7f}; ///< Transparent wheat color.

        constexpr Color Yellow{1.0f, 1.0f, 0.0f,
                               1.0f}; ///< Yellow color.

        constexpr Color YellowTransparent{
            1.0f, 1.0f, 0.0f,
            0.7f}; ///< Transparent yellow color.
    }
}