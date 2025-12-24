/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Theme0Properties.hpp"
#include "Common/Matter/Coloring/Palette.hpp"

namespace Forradia::Theme0
{
    auto Theme0Properties::getGameWindowTitle() -> std::string
    {
        return "Forradia";
    }

    auto Theme0Properties::getClearColor() -> Color
    {
        return Palette::getColor<hash("MildBlue")>();
    }

    auto Theme0Properties::getGridSize() -> Size
    {
        return {45, 45};
    }

    auto Theme0Properties::getBaseWorldAreaSize() -> Size
    {
        return {120, 100};
    }

    auto Theme0Properties::getWorldScaling() -> float
    {
        return 5.0F;
    }

    auto Theme0Properties::getTileSize() -> float
    {
        return 2.2F;
    }

    auto Theme0Properties::getElevationHeight() -> float
    {
        return 0.15F;
    }
}
