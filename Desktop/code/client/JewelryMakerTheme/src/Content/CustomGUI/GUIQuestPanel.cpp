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
            constexpr RectF questTitleTextPanelBounds{0.01F, 0.01F, 0.1F, 0.05F};

            m_questTitleTextPanel =
                std::make_shared<GUILabel>("GUILabelQuestTitlePanel",
                                        questTitleTextPanelBounds.x, questTitleTextPanelBounds.y,
                                        questTitleTextPanelBounds.width, questTitleTextPanelBounds.height,
                                        "Current Quest", false, Palette::getColor<hash("Yellow")>());

            this->addChildComponent(m_questTitleTextPanel);
        // clang-format on

        /* Add the quest name text panel */ // clang-format off
            constexpr RectF questNameTextPanelBounds{0.01F, 0.041F, 0.1F, 0.05F};

            m_questNameTextPanel =
                std::make_shared<GUILabel>("GUILabelQuestNamePanel",
                                        questNameTextPanelBounds.x, questNameTextPanelBounds.y,
                                        questNameTextPanelBounds.width, questNameTextPanelBounds.height);

            this->addChildComponent(m_questNameTextPanel);
        // clang-format on

        /* Add the quest description text panel */ // clang-format off
            constexpr RectF questDescriptionTextPanelBounds{0.01F, 0.069F, 0.1F, 0.05F};

            m_questDescriptionTextPanel =
            std::make_shared<GUILabel>("GUILabelQuestDescriptionPanel",
                                        questDescriptionTextPanelBounds.x, questDescriptionTextPanelBounds.y,
                                        questDescriptionTextPanelBounds.width, questDescriptionTextPanelBounds.height);

            this->addChildComponent(m_questDescriptionTextPanel);
        // clang-format on

        /* Add the quest status text panel */ // clang-format off
            constexpr RectF questStatusTextPanelBounds{0.01F, 0.097F, 0.1F, 0.05F};

            m_questStatusTextPanel =
                std::make_shared<GUILabel>("GUILabelQuestStatusPanel",
                                          questStatusTextPanelBounds.x, questStatusTextPanelBounds.y,
                                          questStatusTextPanelBounds.width, questStatusTextPanelBounds.height);

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
