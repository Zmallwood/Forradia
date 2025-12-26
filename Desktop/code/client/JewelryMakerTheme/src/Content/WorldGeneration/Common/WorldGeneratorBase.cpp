/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "WorldGeneratorBase.hpp"
    #include "Content/Properties/ThemeProperties.hpp"
    #include "Content/WorldStructure/World.hpp"
    #include "Content/WorldStructure/WorldArea.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto WorldGeneratorBase::prepare() -> void
    {
        m_worldArea = JewelryMakerTheme::World::instance().getCurrentWorldArea();
        m_worldAreaSize = m_worldArea->getSize();
        m_worldScaling = JewelryMakerTheme::ThemeProperties::getWorldScaling();
    }

    auto WorldGeneratorBase::getDistance(int x1, int y1, int x2, int y2) -> float
    {
        auto dx{static_cast<float>(x2 - x1)};
        auto dy{static_cast<float>(y2 - y1)};

        return std::sqrt(dx * dx + dy * dy);
    }
}
