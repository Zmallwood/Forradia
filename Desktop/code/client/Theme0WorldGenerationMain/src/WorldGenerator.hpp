/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  class WorldArea;

  /**
   * The WorldGenerator class is responsible for generating a new world.
   */
  class WorldGenerator {
   public:
    /**
     * Generates a new world.
     */
    auto GenerateNewWorld() const -> void;

   private:
    auto Prepare() const -> void;
  };
}
