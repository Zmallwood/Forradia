/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
  /**
   * Randomize the seed.
   */
  auto Randomize() -> void;

  /**
   * Generate a random integer.
   *
   * @param upperLimit Upper limit.
   * @return Random integer.
   */
  auto GetRandomInt(int upperLimit) -> int;
}
