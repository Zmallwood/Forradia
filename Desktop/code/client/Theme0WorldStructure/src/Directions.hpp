//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#pragma once

namespace Forradia::Theme0 {
/// Compass directions in the game world.
enum class Directions {
  None,      ///< No direction.
  North,     ///< North direction.
  East,      ///< East direction.
  South,     ///< South direction.
  West,      ///< West direction.
  NorthEast, ///< North-east direction.
  SouthEast, ///< South-east direction.
  SouthWest, ///< South-west direction.
  NorthWest  ///< North-west direction.
};
}