/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Forradia::Theme0
{
    class Quest;

    /**
     * Manages the quests in the game.
     */
    class QuestSystem
    {
      public:
        static auto Instance() -> QuestSystem &
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
            this->Initialize();
        }

        /**
         * Updates the quest system.
         */
        auto Update() const -> void;

        /**
         * Gets the name of the current quest.
         */
        [[nodiscard]] auto GetCurrentQuestName() const -> std::string;

        /**
         * Gets the description of the current quest.
         */
        [[nodiscard]] auto GetCurrentQuestDescription() const -> std::string;

        /**
         * Gets the status of the current quest.
         */
        [[nodiscard]] auto GetCurrentQuestStatus() const -> std::string;

      private:
        auto Initialize() -> void;

        std::vector<std::shared_ptr<Quest>> m_quests{};
    };
}
