/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <string>

namespace ForradiaEngine::JewelryMakerTheme
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
         *
         *  @return The status of the quest.
         */
        [[nodiscard]] virtual auto getStatus() const -> std::string = 0;

        /** The name of the quest. */
        std::string name{};

        /** The description of the quest. */
        std::string description{};

        /** Whether the quest is completed. */
        bool isCompleted{false};
    };
}
