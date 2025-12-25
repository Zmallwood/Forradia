/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <string>

namespace Forradia::Theme0
{
    /**
     *  A quest is a task that the player can complete to progress the game.
     */
    class Quest
    {
      public:
        virtual ~Quest() = default;

        /**
         *  Updates the quest.
         */
        virtual auto update() -> void = 0;

        /**
         *  Gets the status of the quest.
         */
        [[nodiscard]] virtual auto getStatus() const -> std::string = 0;

        std::string name{};        ///< The name of the quest.
        std::string description{}; ///< The description of the quest.
        bool isCompleted{false};   ///< Whether the quest is completed.
    };
}
