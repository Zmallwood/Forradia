/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "quests.hpp"
#include "Player/Player.hpp"
#include "WorldStructure/ObjectsStack.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto MoveQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto numSteps{0};

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::MoveNorth || action == PlayerActionTypes::MoveEast ||
               action == PlayerActionTypes::MoveSouth || action == PlayerActionTypes::MoveWest ||
               action == PlayerActionTypes::MoveNorthEast ||
               action == PlayerActionTypes::MoveSouthEast ||
               action == PlayerActionTypes::MoveSouthWest ||
               action == PlayerActionTypes::MoveNorthWest)
            {
                numSteps++;
            }
        }

        m_numStepsLeft = 10 - numSteps;

        If(numSteps >= 10)
        {
            isCompleted = true;

            GUIChatBox::instance().print("Quest completed: Movement. Obtained 50 XP.");

            // NOLINTNEXTLINE(readability-magic-numbers)
            Player::instance().addExperience(50);
        }
    }

    auto MoveQuest::getStatus() const -> std::string
    {
        return "Movements left: " + std::to_string(m_numStepsLeft);
    }

    auto ForageQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto numForagings{0};

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Forage)
            {
                numForagings++;
            }
        }

        m_numForagingsLeft = 3 - numForagings;

        If(numForagings >= 3)
        {
            isCompleted = true;

            GUIChatBox::instance().print("Quest completed: Forage. Obtained 50 XP.");

            // NOLINTNEXTLINE(readability-magic-numbers)
            Player::instance().addExperience(50);
        }
    }

    auto ForageQuest::getStatus() const -> std::string
    {
        return "Forages left: " + std::to_string(m_numForagingsLeft);
    }

    auto CraftStonePickaxeQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto idx{0};

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Pick)
            {
                If(actionFirstArg == hash("ObjectBranch"))
                {
                    m_numBranchPicked = true;
                    Player::instance().getQuestCompletionPointsRef()["CraftStonePickaxeQuest"] =
                        idx;
                }

                If(actionFirstArg == hash("ObjectStone"))
                {
                    m_numStonePicked = true;
                }
            }

            If(action == PlayerActionTypes::Craft)
            {
                If(actionFirstArg == hash("ObjectStonePickaxe"))
                {
                    isCompleted = true;
                }
            }

            idx++;
        }
    }

    auto CraftStonePickaxeQuest::getStatus() const -> std::string
    {
        If(!m_numBranchPicked)
        {
            return "Pick a branch.";
        }

        If(!m_numStonePicked)
        {
            return "Branch picked. Now pick a stone.";
        }

        return "Craft a stone pickaxe out of the branch and stone.";
    }

    auto CraftStoneBowlQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto idx{0};

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Mine && actionFirstArg == hash("ObjectStone"))
            {
                m_stonedMined = true;

                Player::instance().getQuestCompletionPointsRef()["MineStoneFromCraftStoneBowl"] =
                    idx;
            }

            If(action == PlayerActionTypes::Craft)
            {
                If(actionFirstArg == hash("ObjectStoneBowl"))
                {
                    isCompleted = true;
                }
            }

            idx++;
        }
    }

    auto CraftStoneBowlQuest::getStatus() const -> std::string
    {
        If(!m_stonedMined)
        {
            return "Mine a stone.";
        }

        return "Craft a stone bowl out of the stone.";
    }

    auto PutForagedItemsInStoneBowlQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};
            auto actionThirdArg{get<3>(entry)};

            If(action == PlayerActionTypes::Move)
            {
                If(actionFirstArg == hash("ObjectStoneBowl"))
                {
                    auto movedObject{actionThirdArg};

                    If(movedObject->getType() == hash("ObjectBlueberries"))
                    {
                        isCompleted = true;
                    }
                }
            }
        }
    }

    auto PutForagedItemsInStoneBowlQuest::getStatus() const -> std::string
    {
        return "Put foraged items in the stone bowl.";
    }

    auto CraftCampfireQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto idx{0};

        auto previousBranchPickQuestCompletionPoint{
            Player::instance().getQuestCompletionPointsRef()["CraftStonePickaxeQuest"]};

        auto numPickedBranches{0};

        for (const auto &entry : playerActions)
        {
            If(idx <= previousBranchPickQuestCompletionPoint)
            {
                idx++;

                continue;
            }

            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Pick && actionFirstArg == hash("ObjectBranch"))
            {
                ++numPickedBranches;
            }

            If(action == PlayerActionTypes::Craft)
            {
                If(actionFirstArg == hash("ObjectUnlitCampfire"))
                {
                    isCompleted = true;
                }
            }

            idx++;
        }

        m_numBranchesLeft = k_numBranchesNeeded - numPickedBranches;
    }

    auto CraftCampfireQuest::getStatus() const -> std::string
    {
        If(m_numBranchesLeft > 0)
        {
            return "Branches left: " + std::to_string(m_numBranchesLeft);
        }

        return "Craft the campfire.";
    }

    auto MineStoneFromBoulderQuest1::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto numMinedStones{0};

        auto idx{0};

        auto previousMineQuestCompletionPoint{
            Player::instance().getQuestCompletionPointsRef()["MineStoneFromCraftStoneBowl"]};

        for (const auto &entry : playerActions)
        {
            If(idx <= previousMineQuestCompletionPoint)
            {
                idx++;

                continue;
            }

            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Mine && actionFirstArg == hash("ObjectStone"))
            {
                numMinedStones++;

                If(numMinedStones == k_numStonesNeeded)
                {
                    Player::instance().getQuestCompletionPointsRef()["MineStoneFromBoulderQuest1"] =
                        idx;

                    break;
                }
            }

            idx++;
        }

        m_numMinedStonesLeft = k_numStonesNeeded - numMinedStones;

        If(numMinedStones >= k_numStonesNeeded)
        {
            isCompleted = true;

            GUIChatBox::instance().print("Quest completed: Mine Stone. Obtained 50 XP.");

            // NOLINTNEXTLINE(readability-magic-numbers)
            Player::instance().addExperience(50);
        }
    }

    auto MineStoneFromBoulderQuest1::getStatus() const -> std::string
    {
        return "Stones left: " + std::to_string(m_numMinedStonesLeft);
    }

    auto CraftStoneSlabsQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto numCraftedSlabs{0};

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Craft)
            {
                If(actionFirstArg == hash("ObjectStoneSlab"))
                {
                    numCraftedSlabs++;
                }
            }
        }

        m_numCraftedSlabsLeft = k_numSlabsNeeded - numCraftedSlabs;

        If(numCraftedSlabs >= k_numSlabsNeeded)
        {
            isCompleted = true;

            GUIChatBox::instance().print("Quest completed: Craft Stone Slabs. Obtained 50 XP.");

            // NOLINTNEXTLINE(readability-magic-numbers)
            Player::instance().addExperience(50);
        }
    }

    auto CraftStoneSlabsQuest::getStatus() const -> std::string
    {
        return "Slabs left: " + std::to_string(m_numCraftedSlabsLeft);
    }

    auto LayStoneSlabsQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto numLaidSlabs{0};

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Lay)
            {
                numLaidSlabs++;
            }
        }

        m_numLaidSlabsLeft = k_numSlabsPlacedNeeded - numLaidSlabs;

        If(numLaidSlabs >= k_numSlabsPlacedNeeded)
        {
            isCompleted = true;

            GUIChatBox::instance().print("Quest completed: Lay Stone Slabs. Obtained 50 XP.");

            // NOLINTNEXTLINE(readability-magic-numbers)
            Player::instance().addExperience(50);
        }
    }

    auto LayStoneSlabsQuest::getStatus() const -> std::string
    {
        return "Slabs left: " + std::to_string(m_numLaidSlabsLeft);
    }

    auto MineStoneFromBoulderQuest2::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto numMinedStones{0};

        auto idx{0};

        auto previousMineQuestCompletionPoint{
            Player::instance().getQuestCompletionPointsRef()["MineStoneFromBoulderQuest1"]};

        for (const auto &entry : playerActions)
        {
            If(idx <= previousMineQuestCompletionPoint)
            {
                idx++;
                continue;
            }

            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Mine && actionFirstArg == hash("ObjectStone"))
            {
                numMinedStones++;
            }

            idx++;
        }

        m_numMinedStonesLeft = k_numMinedStonesNeeded - numMinedStones;

        If(numMinedStones >= k_numMinedStonesNeeded)
        {
            isCompleted = true;

            GUIChatBox::instance().print("Quest completed: Mine Stone. Obtained 50 XP.");

            // NOLINTNEXTLINE(readability-magic-numbers)
            Player::instance().addExperience(50);
        }
    }

    auto MineStoneFromBoulderQuest2::getStatus() const -> std::string
    {
        return "Stones left: " + std::to_string(m_numMinedStonesLeft);
    }

    auto CraftStoneBricksQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto numCraftedBricks{0};

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Craft)
            {
                If(actionFirstArg == hash("ObjectStoneBrick"))
                {
                    numCraftedBricks++;
                }
            }
        }

        m_numCraftedBricksLeft = k_numCraftedBricksNeeded - numCraftedBricks;

        If(numCraftedBricks >= k_numCraftedBricksNeeded)
        {
            isCompleted = true;

            GUIChatBox::instance().print("Quest completed: Craft Stone Bricks. Obtained 50 XP.");

            // NOLINTNEXTLINE(readability-magic-numbers)
            Player::instance().addExperience(50);
        }
    }

    auto CraftStoneBricksQuest::getStatus() const -> std::string
    {
        return "Bricks left: " + std::to_string(m_numCraftedBricksLeft);
    }

    auto BuildStoneWallsQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        std::set<Point> wallPositions;

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            auto actionSecondArg{get<2>(entry)};

            If(action == PlayerActionTypes::Craft &&
               (actionFirstArg == hash("ObjectStoneWall") ||
                actionFirstArg == hash("ObjectStoneWallDoor")))
            {
                wallPositions.insert({actionSecondArg.x, actionSecondArg.y});
            }
        }

        auto numIncompleteWallTiles{BuildStoneWallsQuest::getNumIncompleteWallTiles(wallPositions)};

        If(!wallPositions.empty() && numIncompleteWallTiles == 0)
        {
            isCompleted = true;

            GUIChatBox::instance().print("Quest completed: Build Stone Walls. Obtained 50 XP.");

            // NOLINTNEXTLINE(readability-magic-numbers)
            Player::instance().addExperience(50);
        }
    }

    auto BuildStoneWallsQuest::getNumIncompleteWallTiles(const std::set<Point> &wallPositions)
        -> int
    {
        auto worldArea{World::instance().getWorldArea(Player::instance().getWorldAreaCoordinate())};

        auto numIncompleteWallTiles{0};

        for (const auto &position : wallPositions)
        {
            auto tileNorth{worldArea->getTile(position.x, position.y - 1)};
            auto tileSouth{worldArea->getTile(position.x, position.y + 1)};
            auto tileWest{worldArea->getTile(position.x - 1, position.y)};
            auto tileEast{worldArea->getTile(position.x + 1, position.y)};
            auto tileNorthEast{worldArea->getTile(position.x + 1, position.y - 1)};
            auto tileSouthEast{worldArea->getTile(position.x + 1, position.y + 1)};
            auto tileSouthWest{worldArea->getTile(position.x - 1, position.y + 1)};
            auto tileNorthWest{worldArea->getTile(position.x - 1, position.y - 1)};

            std::vector<std::shared_ptr<Tile>> tilesWithDiagonals{
                tileNorth,     tileSouth,     tileWest,      tileEast,
                tileNorthEast, tileSouthEast, tileSouthWest, tileNorthWest};

            std::vector<std::shared_ptr<Tile>> tilesWithoutDiagonals{tileNorth, tileSouth, tileWest,
                                                                     tileEast};

            auto adjacentStoneSlabTiles{0};

            for (const auto &tile : tilesWithDiagonals)
            {
                If(tile && tile->getGround() == hash("GroundStoneSlab"))
                {
                    adjacentStoneSlabTiles++;
                }
            }

            auto adjacentStoneWallOrDoorTiles{0};

            for (const auto &tile : tilesWithoutDiagonals)
            {
                If(tile && (tile->getObjectsStack()->countHasObject("ObjectStoneWall") > 0 ||
                            tile->getObjectsStack()->countHasObject("ObjectStoneWallDoor") > 0))
                {
                    adjacentStoneWallOrDoorTiles++;
                }
            }

            If(adjacentStoneSlabTiles < 1 || adjacentStoneWallOrDoorTiles < 2)
            {
                numIncompleteWallTiles++;
            }
        }

        return numIncompleteWallTiles;
    }

    auto BuildStoneWallsQuest::getStatus() const -> std::string
    {
        return "You need to build more stone walls (and door).";
    }

    // TODO: Think about if this should be kept or not.
    // auto PlaceSpouseQuest::update() -> void
    // {
    // }

    // auto PlaceSpouseQuest::getStatus() const -> std::string
    // {
    //     return "Place your spouse in the house.";
    // }
}
