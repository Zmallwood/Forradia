/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "Color.hpp"
// clang-format on

namespace ForradiaEngine::Palette
{
    /**
     *   Get a color from the palette.
     *
     *  @tparam N The hash of the name of the color to get.
     *  @return The color.
     */
    template <int N>
    // ReSharper disable once CppFunctionIsNotImplemented
    auto getColor() -> Color;
}
