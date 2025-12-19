/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "QuestSystem.hpp"
#include "Quest.hpp"
#include "Quests.hpp"

namespace Forradia::Theme0 {
  auto QuestSystem::Initialize() -> void {
    m_quests.push_back(std::make_shared<MoveQuest>());
    m_quests.push_back(std::make_shared<ForageQuest>());
    m_quests.push_back(std::make_shared<CraftStonePickaxeQuest>());
    m_quests.push_back(std::make_shared<CraftStoneBowl>());
    m_quests.push_back(std::make_shared<MineStoneFromBoulderQuest1>());
    m_quests.push_back(std::make_shared<CraftStoneSlabsQuest>());
    m_quests.push_back(std::make_shared<LayStoneSlabsQuest>());
    m_quests.push_back(std::make_shared<MineStoneFromBoulderQuest2>());
    m_quests.push_back(std::make_shared<CraftStoneBricksQuest>());
    m_quests.push_back(std::make_shared<BuildStoneWallsQuest>());
  }

  auto QuestSystem::Update() -> void {
    for (auto &quest : this->m_quests) {
      if (quest->isCompleted)
        continue;

      quest->Update();

      return;
    }
  }

  auto QuestSystem::GetCurrentQuestName() const -> String {
    for (auto &quest : this->m_quests) {
      if (quest->isCompleted)
        continue;

      return quest->name;
    }

    return "No quest";
  }

  auto QuestSystem::GetCurrentQuestDescription() const -> String {
    for (auto &quest : this->m_quests) {
      if (quest->isCompleted)
        continue;

      return quest->description;
    }
    return "";
  }

  auto QuestSystem::GetCurrentQuestStatus() const -> String {
    for (auto &quest : this->m_quests) {
      if (quest->isCompleted)
        continue;

      return quest->GetStatus();
    }

    return "";
  }
}
