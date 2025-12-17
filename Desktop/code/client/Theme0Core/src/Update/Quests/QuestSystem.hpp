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
  void Update();

  /**
   * Gets the name of the current quest.
   */
  String GetCurrentQuestName() const;

  /**
   * Gets the description of the current quest.
   */
  String GetCurrentQuestDescription() const;

  /**
   * Gets the status of the current quest.
   */
  String GetCurrentQuestStatus() const;

 private:
  void Initialize();

  Vector<SharedPtr<Quest>> m_quests;
};
}