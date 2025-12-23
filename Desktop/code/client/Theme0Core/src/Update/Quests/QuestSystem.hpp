/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Forradia::Theme0
{
    class Quest;

    /**
     * Manages the quests in the game.
     */
    class QuestSystem
    {
      public:
        static auto instance() -> QuestSystem &
        {
            static QuestSystem instance;
            return instance;
        }

        // Delete copy/move
        QuestSystem(const QuestSystem &) = delete;

        auto operator=(const QuestSystem &) -> QuestSystem & = delete;

        /**
         * Constructor.
         */
        QuestSystem()
        {
            this->initialize();
        }

        /**
         * Updates the quest system.
         */
        auto update() const -> void;

        /**
         * Gets the name of the current quest.
         */
        [[nodiscard]] auto getCurrentQuestName() const -> std::string;

        /**
         * Gets the description of the current quest.
         */
        [[nodiscard]] auto getCurrentQuestDescription() const -> std::string;

        /**
         * Gets the status of the current quest.
         */
        [[nodiscard]] auto getCurrentQuestStatus() const -> std::string;

      private:
        auto initialize() -> void;

        std::vector<std::shared_ptr<Quest>> m_quests{};
    };
}
