/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia::Theme0 {
  class Quest;

  /**
   * Manages the quests in the game.
   */
  class QuestSystem {
   public:
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
    auto GetCurrentQuestName() const -> String;

    /**
     * Gets the description of the current quest.
     */
    auto GetCurrentQuestDescription() const -> String;

    /**
     * Gets the status of the current quest.
     */
    auto GetCurrentQuestStatus() const -> String;

   private:
    auto Initialize() -> void;

    Vector<SharedPtr<Quest>> m_quests;
  };
}
