/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ThemeProperties.hpp"
    #include "ForradiaEngine/Common/Matter/Coloring.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto ThemeProperties::getGameWindowTitle() -> std::string
    {
        return "Forradia";
    }

    auto ThemeProperties::getClearColor() -> Color
    {
        return Palette::getColor<hash("MildBlue")>();
    }

    auto ThemeProperties::getGridSize() -> Size
    {
        return {45, 45};
    }

    auto ThemeProperties::getBaseWorldAreaSize() -> Size
    {
        return {120, 100};
    }

    auto ThemeProperties::getWorldScaling() -> float
    {
        return 5.0F;
    }

    auto ThemeProperties::getTileSize() -> float
    {
        return 2.2F;
    }

    auto ThemeProperties::getElevationHeight() -> float
    {
        return 0.15F;
    }
}
