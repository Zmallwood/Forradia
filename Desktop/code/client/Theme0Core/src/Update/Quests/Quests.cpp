//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO

#include "Quests.hpp"
#include "GUIChatBox.hpp"
#include "Player/PlayerCharacter.hpp"

namespace Forradia::Theme0::GameplayCore
{
    void MoveQuest::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numSteps{0};

        for (auto &entry : playerActions)
        {
            auto action{entry.first};
            if (action == PlayerActionTypes::MoveNorth || action == PlayerActionTypes::MoveEast ||
                action == PlayerActionTypes::MoveSouth || action == PlayerActionTypes::MoveWest)
            {
                numSteps++;
            }
        }
        m_numStepsLeft = 3 - numSteps;
        if (numSteps >= 3)
        {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Movement. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }

        return;
    }

    String MoveQuest::GetStatus() const
    {
        return "Movements left: " + std::to_string(m_numStepsLeft);
    }

    void ForageQuest::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numForagings{0};

        for (auto &entry : playerActions)
        {
            auto action{entry.first};
            if (action == PlayerActionTypes::Forage)
            {
                numForagings++;
            }
        }

        m_numForagingsLeft = 3 - numForagings;

        if (numForagings >= 3)
        {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Forage. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String ForageQuest::GetStatus() const
    {
        return "Forages left: " + std::to_string(m_numForagingsLeft);
    }

    void CraftStonePickaxeQuest::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        for (auto &entry : playerActions)
        {
            auto action{entry.first};
            if (action == PlayerActionTypes::Pick)
            {
                if (entry.second == "ObjectBranch")
                {
                    m_numBranchPicked = true;
                }
                if (entry.second == "ObjectStone")
                {
                    m_numStonePicked = true;
                }
            }
            if (action == PlayerActionTypes::Craft)
            {
                if (entry.second == "ObjectStonePickaxe")
                {
                    isCompleted = true;
                }
            }
        }
    }

    String CraftStonePickaxeQuest::GetStatus() const
    {
        if (!m_numBranchPicked)
        {
            return "Pick a branch.";
        }

        if (!m_numStonePicked)
        {
            return "Branch picked. Now pick a stone.";
        }
        return "Craft a stone pickaxe out of the branch and stone.";
    }

    void MineStoneFromBoulderQuest1::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numMinedStones{0};
        auto i{0};

        for (auto &entry : playerActions)
        {
            auto action{entry.first};

            if (action == PlayerActionTypes::Mine && entry.second == "ObjectStone")
            {
                numMinedStones++;

                if (numMinedStones == 10)
                {
                    _<PlayerCharacter>()
                        .GetQuestCompletionPointsRef()["MineStoneFromBoulderQuest1"] = i;
                    break;
                }
            }

            i++;
        }

        m_numMinedStonesLeft = 10 - numMinedStones;

        if (numMinedStones >= 10)
        {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Mine Stone. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String MineStoneFromBoulderQuest1::GetStatus() const
    {
        return "Stones left: " + std::to_string(m_numMinedStonesLeft);
    }

    void CraftStoneSlabsQuest::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numCraftedSlabs{0};

        for (auto &entry : playerActions)
        {
            auto action{entry.first};

            if (action == PlayerActionTypes::Craft)
            {
                if (entry.second == "ObjectStoneSlab")
                {
                    numCraftedSlabs++;
                }
            }
        }

        m_numCraftedSlabsLeft = 10 - numCraftedSlabs;

        if (numCraftedSlabs >= 10)
        {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Craft Stone Slabs. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String CraftStoneSlabsQuest::GetStatus() const
    {
        return "Slabs left: " + std::to_string(m_numCraftedSlabsLeft);
    }

    void LayStoneSlabsQuest::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numLaidSlabs{0};

        for (auto &entry : playerActions)
        {
            auto action{entry.first};
            if (action == PlayerActionTypes::Lay)
            {
                numLaidSlabs++;
            }
        }

        m_numLaidSlabsLeft = 10 - numLaidSlabs;

        if (numLaidSlabs >= 10)
        {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Lay Stone Slabs. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String LayStoneSlabsQuest::GetStatus() const
    {
        return "Slabs left: " + std::to_string(m_numLaidSlabsLeft);
    }

    void MineStoneFromBoulderQuest2::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numMinedStones{0};
        auto i{0};
        auto previousMineQuestCompletionPoint{
            _<PlayerCharacter>().GetQuestCompletionPointsRef()["MineStoneFromBoulderQuest1"]};

        for (auto &entry : playerActions)
        {
            if (i <= previousMineQuestCompletionPoint)
            {
                i++;
                continue;
            }

            auto action{entry.first};

            if (action == PlayerActionTypes::Mine && entry.second == "ObjectStone")
            {
                numMinedStones++;
            }

            i++;
        }

        m_numMinedStonesLeft = 10 - numMinedStones;

        if (numMinedStones >= 10)
        {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Mine Stone. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String MineStoneFromBoulderQuest2::GetStatus() const
    {
        return "Stones left: " + std::to_string(m_numMinedStonesLeft);
    }

    void CraftStoneBricksQuest::Update()
    {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numCraftedBricks{0};

        for (auto &entry : playerActions)
        {
            auto action{entry.first};

            if (action == PlayerActionTypes::Craft)
            {
                if (entry.second == "ObjectStoneBrick")
                {
                    numCraftedBricks++;
                }
            }
        }

        m_numCraftedBricksLeft = 10 - numCraftedBricks;

        if (numCraftedBricks >= 10)
        {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Craft Stone Bricks. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String CraftStoneBricksQuest::GetStatus() const
    {
        return "Bricks left: " + std::to_string(m_numCraftedBricksLeft);
    }
}