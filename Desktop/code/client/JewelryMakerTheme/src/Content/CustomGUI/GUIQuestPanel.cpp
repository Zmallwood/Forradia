/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIQuestPanel.hpp"

#include "Content/Core/Update/Quests/QuestSystem.hpp"
#include "ForradiaEngine/GUICore/GUILabel.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIQuestPanel::initialize() -> void
    {
        constexpr RectF questTitleTextPanelBounds{0.01F, 0.01F, 0.1F, 0.05F};

        m_questTitleTextPanel = std::make_shared<GUILabel>(
            "GUILabelQuestTitlePanel", questTitleTextPanelBounds.x, questTitleTextPanelBounds.y,
            questTitleTextPanelBounds.width, questTitleTextPanelBounds.height, "Current Quest",
            false, Palette::getColor<hash("Yellow")>());

        this->addChildComponent(m_questTitleTextPanel);

        constexpr RectF questNameTextPanelBounds{0.01F, 0.041F, 0.1F, 0.05F};

        m_questNameTextPanel = std::make_shared<GUILabel>(
            "GUILabelQuestNamePanel", questNameTextPanelBounds.x, questNameTextPanelBounds.y,
            questNameTextPanelBounds.width, questNameTextPanelBounds.height);

        this->addChildComponent(m_questNameTextPanel);

        constexpr RectF questDescriptionTextPanelBounds{0.01F, 0.069F, 0.1F, 0.05F};

        m_questDescriptionTextPanel = std::make_shared<GUILabel>(
            "GUILabelQuestDescriptionPanel", questDescriptionTextPanelBounds.x,
            questDescriptionTextPanelBounds.y, questDescriptionTextPanelBounds.width,
            questDescriptionTextPanelBounds.height);

        this->addChildComponent(m_questDescriptionTextPanel);

        constexpr RectF questStatusTextPanelBounds{0.01F, 0.097F, 0.1F, 0.05F};

        m_questStatusTextPanel = std::make_shared<GUILabel>(
            "GUILabelQuestStatusPanel", questStatusTextPanelBounds.x, questStatusTextPanelBounds.y,
            questStatusTextPanelBounds.width, questStatusTextPanelBounds.height);

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
