/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Spouse.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto Spouse::isPlaced() const -> bool
    {
        return m_position.x != -1 && m_position.y != -1;
    }
}