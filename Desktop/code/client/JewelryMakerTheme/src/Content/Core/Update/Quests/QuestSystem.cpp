/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "QuestSystem.hpp"
    #include "Quest.hpp"
    #include "Quests.hpp"
// clang-format on

namespace ForradiaEngine::Theme0
{
    auto QuestSystem::initialize() -> void
    {
        m_quests.push_back(std::make_shared<MoveQuest>());
        m_quests.push_back(std::make_shared<ForageQuest>());
        m_quests.push_back(std::make_shared<CraftStonePickaxeQuest>());
        m_quests.push_back(std::make_shared<CraftStoneBowlQuest>());
        m_quests.push_back(std::make_shared<CraftCampfireQuest>());
        m_quests.push_back(std::make_shared<MineStoneFromBoulderQuest1>());
        m_quests.push_back(std::make_shared<CraftStoneSlabsQuest>());
        m_quests.push_back(std::make_shared<LayStoneSlabsQuest>());
        m_quests.push_back(std::make_shared<MineStoneFromBoulderQuest2>());
        m_quests.push_back(std::make_shared<CraftStoneBricksQuest>());
        m_quests.push_back(std::make_shared<BuildStoneWallsQuest>());
        m_quests.push_back(std::make_shared<PlaceSpouseQuest>());
    }

    auto QuestSystem::update() const -> void
    {
        for (auto &quest : this->m_quests)
        {
            if (quest->isCompleted)
            {
                continue;
            }

            quest->update();

            return;
        }
    }

    auto QuestSystem::getCurrentQuestName() const -> std::string
    {
        for (const auto &quest : this->m_quests)
        {
            if (quest->isCompleted)
            {
                continue;
            }

            return quest->name;
        }

        return "No quest";
    }

    auto QuestSystem::getCurrentQuestDescription() const -> std::string
    {
        for (const auto &quest : this->m_quests)
        {
            if (quest->isCompleted)
            {
                continue;
            }

            return quest->description;
        }
        return "";
    }

    auto QuestSystem::getCurrentQuestStatus() const -> std::string
    {
        for (const auto &quest : this->m_quests)
        {
            if (quest->isCompleted)
            {
                continue;
            }

            return quest->getStatus();
        }

        return "";
    }
}
