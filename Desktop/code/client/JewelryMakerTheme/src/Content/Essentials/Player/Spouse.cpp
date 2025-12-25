/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Spouse.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
{
    auto Spouse::isPlaced() const -> bool
    {
        return m_position.x != -1 && m_position.y != -1;
    }
}