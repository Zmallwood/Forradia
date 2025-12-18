/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  /**
   * Manages the saving and loading of the game.
   */
  class GameSaving {
   public:
    /**
     * Saves the game to a file.
     */
    auto SaveGame() -> void;

    /**
     * Loads the game from a file.
     */
    auto LoadGame() -> void;
  };
}
