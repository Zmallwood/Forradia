/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia::Theme0 {
    class Quest;

    /**
     * Manages the quests in the game.
     */
    class QuestSystem {
      public:
        static QuestSystem &Instance() {
            static QuestSystem instance;
            return instance;
        }

        // Delete copy/move
        QuestSystem(const QuestSystem &) = delete;

        QuestSystem &operator=(const QuestSystem &) = delete;

        /**
         * Constructor.
         */
        QuestSystem() {
            this->Initialize();
        }

        /**
         * Updates the quest system.
         */
        auto Update() -> void;

        /**
         * Gets the name of the current quest.
         */
        auto GetCurrentQuestName() const -> std::string;

        /**
         * Gets the description of the current quest.
         */
        auto GetCurrentQuestDescription() const -> std::string;

        /**
         * Gets the status of the current quest.
         */
        auto GetCurrentQuestStatus() const -> std::string;

      private:
        auto Initialize() -> void;

        std::vector<std::shared_ptr<Quest>> m_quests{};
    };
}
