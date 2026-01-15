/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ThemeProperties.hpp"
#include "ForradiaEngine/Common/Matter/Coloring.hpp"
#include "ForradiaEngine/Common/General.hpp"

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
        constexpr Size k_defaultValue{45, 45};

        return k_defaultValue;
    }

    auto ThemeProperties::getBaseWorldAreaSize() -> Size
    {
        constexpr Size k_defaultValue{120, 100};

        return k_defaultValue;
    }

    auto ThemeProperties::getWorldScaling() -> float
    {
        constexpr float k_defaultValue{5.0F};

        return k_defaultValue;
    }

    auto ThemeProperties::getTileSize() -> float
    {
        constexpr float k_defaultValue{2.2F};

        return k_defaultValue;
    }

    auto ThemeProperties::getElevationHeight() -> float
    {
        constexpr float k_defaultValue{0.15F};

        return k_defaultValue;
    }
}
