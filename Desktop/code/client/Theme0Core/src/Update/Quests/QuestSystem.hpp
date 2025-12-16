//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

namespace Forradia::Theme0 {
class Quest;

class QuestSystem {
 public:
  QuestSystem() {
    this->Initialize();
  }

  void Update();

  String GetCurrentQuestName() const;

  String GetCurrentQuestDescription() const;

  String GetCurrentQuestStatus() const;

 private:
  void Initialize();

  Vector<SharedPtr<Quest>> m_quests;
};
}