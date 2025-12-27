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
        /* Add the quest title text panel */ // clang-format off
            m_questTitleTextPanel =
                std::make_shared<GUILabel>("GUILabelQuestTitlePanel", 0.01f, 0.01f, 0.1f, 0.05f,
                                        "Current Quest", false, Palette::getColor<hash("Yellow")>());

            this->addChildComponent(m_questTitleTextPanel);
        // clang-format on

        /* Add the quest name text panel */ // clang-format off
            m_questNameTextPanel =
                std::make_shared<GUILabel>("GUILabelQuestNamePanel", 0.01f, 0.041f, 0.1f, 0.05f);

            this->addChildComponent(m_questNameTextPanel);
        // clang-format on

        /* Add the quest description text panel */ // clang-format off
            m_questDescriptionTextPanel =
            std::make_shared<GUILabel>("GUILabelQuestDescriptionPanel", 0.01f, 0.069f, 0.1f, 0.05f);

            this->addChildComponent(m_questDescriptionTextPanel);
        // clang-format on

        /* Add the quest status text panel */ // clang-format off
            m_questStatusTextPanel =
                std::make_shared<GUILabel>("GUILabelQuestStatusPanel", 0.01f, 0.097f, 0.1f, 0.05f);

            this->addChildComponent(m_questStatusTextPanel);
        // clang-format on
    }

    auto GUIQuestPanel::updateDerived() -> void
    {
        GUIMovablePanel::updateDerived();

        /* Update the quest name text panel for the current quest */ // clang-format off
            auto questName{QuestSystem::instance().getCurrentQuestName()};

            m_questNameTextPanel->setText(questName);
        // clang-format on

        /* Update the quest description text panel for the current quest */ // clang-format off
            auto questDescription{QuestSystem::instance().getCurrentQuestDescription()};

            m_questDescriptionTextPanel->setText(questDescription);
        // clang-format on

        /* Update the quest status text panel for the current quest */ // clang-format off
            auto questStatus{QuestSystem::instance().getCurrentQuestStatus()};

            m_questStatusTextPanel->setText(questStatus);
        // clang-format on
    }
}
