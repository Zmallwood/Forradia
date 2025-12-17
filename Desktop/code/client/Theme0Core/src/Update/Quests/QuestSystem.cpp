/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "QuestSystem.hpp"
#include "Quest.hpp"
#include "Quests.hpp"

namespace Forradia::Theme0 {
void QuestSystem::Initialize() {
  m_quests.push_back(std::make_shared<MoveQuest>());
  m_quests.push_back(std::make_shared<ForageQuest>());
  m_quests.push_back(std::make_shared<CraftStonePickaxeQuest>());
  m_quests.push_back(std::make_shared<MineStoneFromBoulderQuest1>());
  m_quests.push_back(std::make_shared<CraftStoneSlabsQuest>());
  m_quests.push_back(std::make_shared<LayStoneSlabsQuest>());
  m_quests.push_back(std::make_shared<MineStoneFromBoulderQuest2>());
  m_quests.push_back(std::make_shared<CraftStoneBricksQuest>());
  m_quests.push_back(std::make_shared<BuildStoneWallsQuest>());
}

void QuestSystem::Update() {
  for (auto &quest : this->m_quests) {
    if (quest->isCompleted)
      continue;

    quest->Update();

    return;
  }
}

String QuestSystem::GetCurrentQuestName() const {
  for (auto &quest : this->m_quests) {
    if (quest->isCompleted)
      continue;

    return quest->name;
  }

  return "No quest";
}

String QuestSystem::GetCurrentQuestDescription() const {
  for (auto &quest : this->m_quests) {
    if (quest->isCompleted)
      continue;

    return quest->description;
  }
  return "";
}

String QuestSystem::GetCurrentQuestStatus() const {
  for (auto &quest : this->m_quests) {
    if (quest->isCompleted)
      continue;

    return quest->GetStatus();
  }

  return "";
}
}