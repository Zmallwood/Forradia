/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Theme0Properties.hpp"

namespace Forradia::Theme0
{
    auto Theme0Properties::GetGameWindowTitle() -> std::string
    {
        return "Forradia";
    }

    auto Theme0Properties::GetClearColor() -> Color
    {
        return Palette::GetColor<Hash("MildBlue")>();
    }

    auto Theme0Properties::GetGridSize() -> Size
    {
        return {45, 45};
    }

    auto Theme0Properties::GetBaseWorldAreaSize() -> Size
    {
        return {120, 100};
    }

    auto Theme0Properties::GetWorldScaling() -> float
    {
        return 5.0F;
    }

    auto Theme0Properties::GetTileSize() -> float
    {
        return 2.2F;
    }

    auto Theme0Properties::GetElevationHeight() -> float
    {
        return 0.15F;
    }
}
