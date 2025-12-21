/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Quests.hpp"
#include "GUIChatBox.hpp"
#include "ObjectsStack.hpp"
#include "Player/Player.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
    auto MoveQuest::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        auto numSteps{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::MoveNorth || action == PlayerActionTypes::MoveEast ||
                action == PlayerActionTypes::MoveSouth || action == PlayerActionTypes::MoveWest)
                numSteps++;
        }
        m_numStepsLeft = 3 - numSteps;
        if (numSteps >= 3) {
            isCompleted = true;
            Singleton<GUIChatBox>().Print("Quest completed: Movement. Obtained 50 XP.");
            Singleton<Player>().AddExperience(50);
        }

        return;
    }

    auto MoveQuest::GetStatus() const -> std::string {
        return "Movements left: " + std::to_string(m_numStepsLeft);
    }

    auto ForageQuest::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        auto numForagings{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Forage)
                numForagings++;
        }

        m_numForagingsLeft = 3 - numForagings;

        if (numForagings >= 3) {
            isCompleted = true;
            Singleton<GUIChatBox>().Print("Quest completed: Forage. Obtained 50 XP.");
            Singleton<Player>().AddExperience(50);
        }
    }

    auto ForageQuest::GetStatus() const -> std::string {
        return "Forages left: " + std::to_string(m_numForagingsLeft);
    }

    auto CraftStonePickaxeQuest::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Pick) {
                if (actionFirstArg == "ObjectBranch")
                    m_numBranchPicked = true;
                if (actionFirstArg == "ObjectStone")
                    m_numStonePicked = true;
            }
            if (action == PlayerActionTypes::Craft) {
                if (actionFirstArg == "ObjectStonePickaxe")
                    isCompleted = true;
            }
        }
    }

    auto CraftStonePickaxeQuest::GetStatus() const -> std::string {
        if (!m_numBranchPicked)
            return "Pick a branch.";

        if (!m_numStonePicked)
            return "Branch picked. Now pick a stone.";

        return "Craft a stone pickaxe out of the branch and stone.";
    }

    auto CraftStoneBowl::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        auto i{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Mine && actionFirstArg == "ObjectStone") {
                m_stonedMined = true;
                Singleton<Player>().GetQuestCompletionPointsRef()["MineStoneFromCraftStoneBowl"] =
                    i;
            }
            if (action == PlayerActionTypes::Craft)
                if (actionFirstArg == "ObjectStoneBowl")
                    isCompleted = true;

            i++;
        }
    }

    auto CraftStoneBowl::GetStatus() const -> std::string {
        if (!m_stonedMined)
            return "Mine a stone.";

        return "Craft a stone bowl out of the stone.";
    }

    auto MineStoneFromBoulderQuest1::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        auto numMinedStones{0};
        auto i{0};
        auto previousMineQuestCompletionPoint{
            Singleton<Player>().GetQuestCompletionPointsRef()["MineStoneFromCraftStoneBowl"]};

        for (auto &entry : playerActions) {
            if (i <= previousMineQuestCompletionPoint) {
                i++;
                continue;
            }

            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Mine && actionFirstArg == "ObjectStone") {
                numMinedStones++;

                if (numMinedStones == 10) {
                    Singleton<Player>()
                        .GetQuestCompletionPointsRef()["MineStoneFromBoulderQuest1"] = i;
                    break;
                }
            }

            i++;
        }

        m_numMinedStonesLeft = 10 - numMinedStones;

        if (numMinedStones >= 10) {
            isCompleted = true;
            Singleton<GUIChatBox>().Print("Quest completed: Mine Stone. Obtained 50 XP.");
            Singleton<Player>().AddExperience(50);
        }
    }

    auto MineStoneFromBoulderQuest1::GetStatus() const -> std::string {
        return "Stones left: " + std::to_string(m_numMinedStonesLeft);
    }

    auto CraftStoneSlabsQuest::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        auto numCraftedSlabs{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Craft)
                if (actionFirstArg == "ObjectStoneSlab")
                    numCraftedSlabs++;
        }

        m_numCraftedSlabsLeft = 10 - numCraftedSlabs;

        if (numCraftedSlabs >= 10) {
            isCompleted = true;
            Singleton<GUIChatBox>().Print("Quest completed: Craft Stone Slabs. Obtained 50 XP.");
            Singleton<Player>().AddExperience(50);
        }
    }

    auto CraftStoneSlabsQuest::GetStatus() const -> std::string {
        return "Slabs left: " + std::to_string(m_numCraftedSlabsLeft);
    }

    auto LayStoneSlabsQuest::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        auto numLaidSlabs{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Lay)
                numLaidSlabs++;
        }

        m_numLaidSlabsLeft = 10 - numLaidSlabs;

        if (numLaidSlabs >= 10) {
            isCompleted = true;
            Singleton<GUIChatBox>().Print("Quest completed: Lay Stone Slabs. Obtained 50 XP.");
            Singleton<Player>().AddExperience(50);
        }
    }

    auto LayStoneSlabsQuest::GetStatus() const -> std::string {
        return "Slabs left: " + std::to_string(m_numLaidSlabsLeft);
    }

    auto MineStoneFromBoulderQuest2::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        auto numMinedStones{0};
        auto i{0};
        auto previousMineQuestCompletionPoint{
            Singleton<Player>().GetQuestCompletionPointsRef()["MineStoneFromBoulderQuest1"]};

        for (auto &entry : playerActions) {
            if (i <= previousMineQuestCompletionPoint) {
                i++;
                continue;
            }

            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Mine && actionFirstArg == "ObjectStone")
                numMinedStones++;

            i++;
        }

        m_numMinedStonesLeft = 10 - numMinedStones;

        if (numMinedStones >= 10) {
            isCompleted = true;
            Singleton<GUIChatBox>().Print("Quest completed: Mine Stone. Obtained 50 XP.");
            Singleton<Player>().AddExperience(50);
        }
    }

    auto MineStoneFromBoulderQuest2::GetStatus() const -> std::string {
        return "Stones left: " + std::to_string(m_numMinedStonesLeft);
    }

    auto CraftStoneBricksQuest::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        auto numCraftedBricks{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Craft)
                if (actionFirstArg == "ObjectStoneBrick")
                    numCraftedBricks++;
        }

        m_numCraftedBricksLeft = 10 - numCraftedBricks;

        if (numCraftedBricks >= 10) {
            isCompleted = true;
            Singleton<GUIChatBox>().Print("Quest completed: Craft Stone Bricks. Obtained 50 XP.");
            Singleton<Player>().AddExperience(50);
        }
    }

    auto CraftStoneBricksQuest::GetStatus() const -> std::string {
        return "Bricks left: " + std::to_string(m_numCraftedBricksLeft);
    }

    auto BuildStoneWallsQuest::Update() -> void {
        auto &playerActions{Singleton<Player>().GetPlayerActionsRef()};

        std::set<Point> wallPositions;
        auto numIncompleteWallTiles{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Craft &&
                (actionFirstArg == "ObjectStoneWall" || actionFirstArg == "ObjectStoneWallDoor"))
                wallPositions.insert({actionSecondArg.x, actionSecondArg.y});
        }

        auto worldArea{Singleton<World>().GetCurrentWorldArea()};

        for (auto &position : wallPositions) {
            auto tileNorth{worldArea->GetTile(position.x, position.y - 1)};
            auto tileSouth{worldArea->GetTile(position.x, position.y + 1)};
            auto tileWest{worldArea->GetTile(position.x - 1, position.y)};
            auto tileEast{worldArea->GetTile(position.x + 1, position.y)};
            auto tileNorthEast{worldArea->GetTile(position.x + 1, position.y - 1)};
            auto tileSouthEast{worldArea->GetTile(position.x + 1, position.y + 1)};
            auto tileSouthWest{worldArea->GetTile(position.x - 1, position.y + 1)};
            auto tileNorthWest{worldArea->GetTile(position.x - 1, position.y - 1)};

            auto adjacentStoneSlabTiles{0};

            if (tileNorth && tileNorth->GetGround() == Hash("GroundStoneSlab"))
                adjacentStoneSlabTiles++;
            if (tileSouth && tileSouth->GetGround() == Hash("GroundStoneSlab"))
                adjacentStoneSlabTiles++;
            if (tileWest && tileWest->GetGround() == Hash("GroundStoneSlab"))
                adjacentStoneSlabTiles++;
            if (tileEast && tileEast->GetGround() == Hash("GroundStoneSlab"))
                adjacentStoneSlabTiles++;
            if (tileNorthEast && tileNorthEast->GetGround() == Hash("GroundStoneSlab"))
                adjacentStoneSlabTiles++;
            if (tileSouthEast && tileSouthEast->GetGround() == Hash("GroundStoneSlab"))
                adjacentStoneSlabTiles++;
            if (tileSouthWest && tileSouthWest->GetGround() == Hash("GroundStoneSlab"))
                adjacentStoneSlabTiles++;
            if (tileNorthWest && tileNorthWest->GetGround() == Hash("GroundStoneSlab"))
                adjacentStoneSlabTiles++;

            auto adjacentStoneWallOrDoorTiles{0};

            if (tileNorth &&
                (tileNorth->GetObjectsStack()->CountHasObject("ObjectStoneWall") > 0 ||
                 tileNorth->GetObjectsStack()->CountHasObject("ObjectStoneWallDoor") > 0))
                adjacentStoneWallOrDoorTiles++;
            if (tileSouth &&
                (tileSouth->GetObjectsStack()->CountHasObject("ObjectStoneWall") > 0 ||
                 tileSouth->GetObjectsStack()->CountHasObject("ObjectStoneWallDoor") > 0))
                adjacentStoneWallOrDoorTiles++;
            if (tileWest &&
                (tileWest->GetObjectsStack()->CountHasObject("ObjectStoneWall") > 0 ||
                 tileWest->GetObjectsStack()->CountHasObject("ObjectStoneWallDoor") > 0))
                adjacentStoneWallOrDoorTiles++;
            if (tileEast &&
                (tileEast->GetObjectsStack()->CountHasObject("ObjectStoneWall") > 0 ||
                 tileEast->GetObjectsStack()->CountHasObject("ObjectStoneWallDoor") > 0))
                adjacentStoneWallOrDoorTiles++;

            if (adjacentStoneSlabTiles < 1 || adjacentStoneWallOrDoorTiles < 2)
                numIncompleteWallTiles++;
        }

        if (wallPositions.size() > 0 && numIncompleteWallTiles == 0) {
            isCompleted = true;
            Singleton<GUIChatBox>().Print("Quest completed: Build Stone Walls. Obtained 50 XP.");
            Singleton<Player>().AddExperience(50);
        }
    }

    auto BuildStoneWallsQuest::GetStatus() const -> std::string {
        return "You need to build more stone walls (and door).";
    }
}
