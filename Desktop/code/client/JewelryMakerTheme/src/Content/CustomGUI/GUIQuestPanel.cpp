/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUIQuestPanel.hpp"
    #include "Content/Core/Update/Quests/QuestSystem.hpp"
    #include "ForradiaEngine/GUICore/GUILabel.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIQuestPanel::initialize() -> void
    {
        m_questTitleTextPanel =
            std::make_shared<GUILabel>("GUILabelQuestTitlePanel", 0.01f, 0.01f, 0.1f, 0.05f,
                                       "Current Quest", false, Palette::getColor<hash("Yellow")>());

        m_questNameTextPanel =
            std::make_shared<GUILabel>("GUILabelQuestNamePanel", 0.01f, 0.041f, 0.1f, 0.05f);

        m_questDescriptionTextPanel =
            std::make_shared<GUILabel>("GUILabelQuestDescriptionPanel", 0.01f, 0.069f, 0.1f, 0.05f);

        m_questStatusTextPanel =
            std::make_shared<GUILabel>("GUILabelQuestStatusPanel", 0.01f, 0.097f, 0.1f, 0.05f);

        this->addChildComponent(m_questTitleTextPanel);
        this->addChildComponent(m_questNameTextPanel);
        this->addChildComponent(m_questDescriptionTextPanel);
        this->addChildComponent(m_questStatusTextPanel);
    }

    auto GUIQuestPanel::updateDerived() -> void
    {
        GUIMovablePanel::updateDerived();

        auto questName{QuestSystem::instance().getCurrentQuestName()};
        m_questNameTextPanel->setText(questName);

        auto questDescription{QuestSystem::instance().getCurrentQuestDescription()};
        m_questDescriptionTextPanel->setText(questDescription);

        auto questStatus{QuestSystem::instance().getCurrentQuestStatus()};
        m_questStatusTextPanel->setText(questStatus);
    }
}
