/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  /**
   * Types of player actions.
   */
  enum class PlayerActionTypes {
    None,
    MoveNorth,
    MoveEast,
    MoveSouth,
    MoveWest,
    Forage,
    Pick,
    Craft,
    Mine,
    Lay
  };
}
