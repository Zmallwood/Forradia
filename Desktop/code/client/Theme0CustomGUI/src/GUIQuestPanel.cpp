/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIQuestPanel.hpp"
#include "GUILabel.hpp"
#include "Update/Quests/QuestSystem.hpp"

namespace Forradia::Theme0 {
    auto GUIQuestPanel::Initialize() -> void {
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

    auto GUIQuestPanel::UpdateDerived() -> void {
        GUIMovablePanel::UpdateDerived();

        auto questName{QuestSystem::Instance().GetCurrentQuestName()};
        m_questNameTextPanel->SetText(questName);

        auto questDescription{QuestSystem::Instance().GetCurrentQuestDescription()};
        m_questDescriptionTextPanel->SetText(questDescription);

        auto questStatus{QuestSystem::Instance().GetCurrentQuestStatus()};
        m_questStatusTextPanel->SetText(questStatus);
    }
}
