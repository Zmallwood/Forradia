/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0
{
    /**
     * Manages the saving and loading of the game.
     */
    class GameSaving
    {
      public:
        static auto Instance() -> GameSaving &
        {
            static GameSaving instance;
            return instance;
        }

        // Delete copy/move
        GameSaving(const GameSaving &) = delete;

        auto operator=(const GameSaving &) -> GameSaving & = delete;

        GameSaving() = default;

        /**
         * Saves the game to a file.
         */
        static auto SaveGame() -> void;

        /**
         * Loads the game from a file.
         */
         static auto LoadGame() -> void;
    };
}
