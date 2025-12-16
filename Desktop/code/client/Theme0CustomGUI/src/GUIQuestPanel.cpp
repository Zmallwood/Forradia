//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "GUIQuestPanel.hpp"
#include "GUILabel.hpp"
#include "Update/Quests/QuestSystem.hpp"

namespace Forradia::Theme0 {
void GUIQuestPanel::Initialize() {
  m_questTitleTextPanel =
      std::make_shared<GUILabel>("GUILabelQuestTitlePanel", 0.01f, 0.01f, 0.1f, 0.05f);
  m_questTitleTextPanel->SetText("Current Quest:");
  m_questNameTextPanel =
      std::make_shared<GUILabel>("GUILabelQuestNamePanel", 0.01f, 0.025f, 0.1f, 0.05f);
  m_questDescriptionTextPanel =
      std::make_shared<GUILabel>("GUILabelQuestDescriptionPanel", 0.01f, 0.04f, 0.1f, 0.05f);
  m_questStatusTextPanel =
      std::make_shared<GUILabel>("GUILabelQuestStatusPanel", 0.01f, 0.055f, 0.1f, 0.05f);

  this->AddChildComponent(m_questTitleTextPanel);
  this->AddChildComponent(m_questNameTextPanel);
  this->AddChildComponent(m_questDescriptionTextPanel);
  this->AddChildComponent(m_questStatusTextPanel);
}

void GUIQuestPanel::UpdateDerived() {
  GUIMovablePanel::UpdateDerived();

  auto questName{_<QuestSystem>().GetCurrentQuestName()};
  m_questNameTextPanel->SetText(questName);

  auto questDescription{_<QuestSystem>().GetCurrentQuestDescription()};
  m_questDescriptionTextPanel->SetText(questDescription);

  auto questStatus{_<QuestSystem>().GetCurrentQuestStatus()};
  m_questStatusTextPanel->SetText(questStatus);
}
}