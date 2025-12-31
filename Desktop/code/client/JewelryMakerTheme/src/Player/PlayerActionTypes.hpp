/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Types of player actions.
     */
    enum class PlayerActionTypes
    {
        None,
        MoveNorth,
        MoveEast,
        MoveSouth,
        MoveWest,
        MoveNorthEast,
        MoveSouthEast,
        MoveSouthWest,
        MoveNorthWest,
        Forage,
        Pick,
        Craft,
        Mine,
        Lay,
        Move
    };
}
