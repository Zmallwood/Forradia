//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO

#include "Quests.hpp"
#include "GUIChatBox.hpp"
#include "ObjectsStack.hpp"
#include "Player/PlayerCharacter.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
    void MoveQuest::Update() {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numSteps{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::MoveNorth || action == PlayerActionTypes::MoveEast ||
                action == PlayerActionTypes::MoveSouth || action == PlayerActionTypes::MoveWest) {
                numSteps++;
            }
        }
        m_numStepsLeft = 3 - numSteps;
        if (numSteps >= 3) {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Movement. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }

        return;
    }

    String MoveQuest::GetStatus() const {
        return "Movements left: " + std::to_string(m_numStepsLeft);
    }

    void ForageQuest::Update() {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numForagings{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Forage) {
                numForagings++;
            }
        }

        m_numForagingsLeft = 3 - numForagings;

        if (numForagings >= 3) {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Forage. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String ForageQuest::GetStatus() const {
        return "Forages left: " + std::to_string(m_numForagingsLeft);
    }

    void CraftStonePickaxeQuest::Update() {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Pick) {
                if (actionFirstArg == "ObjectBranch") {
                    m_numBranchPicked = true;
                }
                if (actionFirstArg == "ObjectStone") {
                    m_numStonePicked = true;
                }
            }
            if (action == PlayerActionTypes::Craft) {
                if (actionFirstArg == "ObjectStonePickaxe") {
                    isCompleted = true;
                }
            }
        }
    }

    String CraftStonePickaxeQuest::GetStatus() const {
        if (!m_numBranchPicked) {
            return "Pick a branch.";
        }

        if (!m_numStonePicked) {
            return "Branch picked. Now pick a stone.";
        }
        return "Craft a stone pickaxe out of the branch and stone.";
    }

    void MineStoneFromBoulderQuest1::Update() {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numMinedStones{0};
        auto i{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Mine && actionFirstArg == "ObjectStone") {
                numMinedStones++;

                if (numMinedStones == 10) {
                    _<PlayerCharacter>()
                        .GetQuestCompletionPointsRef()["MineStoneFromBoulderQuest1"] = i;
                    break;
                }
            }

            i++;
        }

        m_numMinedStonesLeft = 10 - numMinedStones;

        if (numMinedStones >= 10) {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Mine Stone. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String MineStoneFromBoulderQuest1::GetStatus() const {
        return "Stones left: " + std::to_string(m_numMinedStonesLeft);
    }

    void CraftStoneSlabsQuest::Update() {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numCraftedSlabs{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Craft) {
                if (actionFirstArg == "ObjectStoneSlab") {
                    numCraftedSlabs++;
                }
            }
        }

        m_numCraftedSlabsLeft = 10 - numCraftedSlabs;

        if (numCraftedSlabs >= 10) {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Craft Stone Slabs. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String CraftStoneSlabsQuest::GetStatus() const {
        return "Slabs left: " + std::to_string(m_numCraftedSlabsLeft);
    }

    void LayStoneSlabsQuest::Update() {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numLaidSlabs{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Lay) {
                numLaidSlabs++;
            }
        }

        m_numLaidSlabsLeft = 10 - numLaidSlabs;

        if (numLaidSlabs >= 10) {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Lay Stone Slabs. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String LayStoneSlabsQuest::GetStatus() const {
        return "Slabs left: " + std::to_string(m_numLaidSlabsLeft);
    }

    void MineStoneFromBoulderQuest2::Update() {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numMinedStones{0};
        auto i{0};
        auto previousMineQuestCompletionPoint{
            _<PlayerCharacter>().GetQuestCompletionPointsRef()["MineStoneFromBoulderQuest1"]};

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
            }

            i++;
        }

        m_numMinedStonesLeft = 10 - numMinedStones;

        if (numMinedStones >= 10) {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Mine Stone. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String MineStoneFromBoulderQuest2::GetStatus() const {
        return "Stones left: " + std::to_string(m_numMinedStonesLeft);
    }

    void CraftStoneBricksQuest::Update() {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        auto numCraftedBricks{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Craft) {
                if (actionFirstArg == "ObjectStoneBrick") {
                    numCraftedBricks++;
                }
            }
        }

        m_numCraftedBricksLeft = 10 - numCraftedBricks;

        if (numCraftedBricks >= 10) {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Craft Stone Bricks. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String CraftStoneBricksQuest::GetStatus() const {
        return "Bricks left: " + std::to_string(m_numCraftedBricksLeft);
    }

    void BuildStoneWallsQuest::Update() {
        auto &playerActions{_<PlayerCharacter>().GetPlayerActionsRef()};

        std::set<Point> wallPositions;
        auto numIncompleteWallTiles{0};

        for (auto &entry : playerActions) {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Craft &&
                (actionFirstArg == "ObjectStoneWall" || actionFirstArg == "ObjectStoneWallDoor")) {
                wallPositions.insert({actionSecondArg.x, actionSecondArg.y});
            }
        }

        auto worldArea{_<World>().GetCurrentWorldArea()};

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

            if (tileNorth && tileNorth->GetGround() == Hash("GroundStoneSlab")) {
                adjacentStoneSlabTiles++;
            }
            if (tileSouth && tileSouth->GetGround() == Hash("GroundStoneSlab")) {
                adjacentStoneSlabTiles++;
            }
            if (tileWest && tileWest->GetGround() == Hash("GroundStoneSlab")) {
                adjacentStoneSlabTiles++;
            }
            if (tileEast && tileEast->GetGround() == Hash("GroundStoneSlab")) {
                adjacentStoneSlabTiles++;
            }
            if (tileNorthEast && tileNorthEast->GetGround() == Hash("GroundStoneSlab")) {
                adjacentStoneSlabTiles++;
            }
            if (tileSouthEast && tileSouthEast->GetGround() == Hash("GroundStoneSlab")) {
                adjacentStoneSlabTiles++;
            }
            if (tileSouthWest && tileSouthWest->GetGround() == Hash("GroundStoneSlab")) {
                adjacentStoneSlabTiles++;
            }
            if (tileNorthWest && tileNorthWest->GetGround() == Hash("GroundStoneSlab")) {
                adjacentStoneSlabTiles++;
            }

            auto adjacentStoneWallOrDoorTiles{0};

            if (tileNorth &&
                (tileNorth->GetObjectsStack()->CountHasObject("ObjectStoneWall") > 0 ||
                 tileNorth->GetObjectsStack()->CountHasObject("ObjectStoneWallDoor") > 0)) {
                adjacentStoneWallOrDoorTiles++;
            }
            if (tileSouth &&
                (tileSouth->GetObjectsStack()->CountHasObject("ObjectStoneWall") > 0 ||
                 tileSouth->GetObjectsStack()->CountHasObject("ObjectStoneWallDoor") > 0)) {
                adjacentStoneWallOrDoorTiles++;
            }
            if (tileWest &&
                (tileWest->GetObjectsStack()->CountHasObject("ObjectStoneWall") > 0 ||
                 tileWest->GetObjectsStack()->CountHasObject("ObjectStoneWallDoor") > 0)) {
                adjacentStoneWallOrDoorTiles++;
            }
            if (tileEast &&
                (tileEast->GetObjectsStack()->CountHasObject("ObjectStoneWall") > 0 ||
                 tileEast->GetObjectsStack()->CountHasObject("ObjectStoneWallDoor") > 0)) {
                adjacentStoneWallOrDoorTiles++;
            }

            if (adjacentStoneSlabTiles < 1 || adjacentStoneWallOrDoorTiles < 2) {
                numIncompleteWallTiles++;
            }
        }

        if (wallPositions.size() > 0 && numIncompleteWallTiles == 0) {
            isCompleted = true;
            _<GUIChatBox>().Print("Quest completed: Build Stone Walls. Obtained 50 XP.");
            _<PlayerCharacter>().AddExperience(50);
        }
    }

    String BuildStoneWallsQuest::GetStatus() const {
        return "You need to build more stone walls (and door).";
    }
}