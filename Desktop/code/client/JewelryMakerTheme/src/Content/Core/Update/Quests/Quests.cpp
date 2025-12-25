/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "Quests.hpp"
    #include "Content/Essentials/Player/Player.hpp"
    #include "Content/WorldStructure/ObjectsStack.hpp"
    #include "Content/WorldStructure/Tile.hpp"
    #include "Content/WorldStructure/World.hpp"
    #include "Content/WorldStructure/WorldArea.hpp" 
    #include "ForradiaEngine/GUICore/GUIChatBox.hpp"
// clang-format on

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

            if (action == PlayerActionTypes::Forage)
            {
                numForagings++;
            }
        }

        m_numForagingsLeft = 3 - numForagings;

        if (numForagings >= 3)
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

            if (action == PlayerActionTypes::Pick)
            {
                if (actionFirstArg == "ObjectBranch")
                {
                    m_numBranchPicked = true;
                    Player::instance().getQuestCompletionPointsRef()["CraftStonePickaxeQuest"] =
                        idx;
                }

                if (actionFirstArg == "ObjectStone")
                {
                    m_numStonePicked = true;
                }
            }

            if (action == PlayerActionTypes::Craft)
            {
                if (actionFirstArg == "ObjectStonePickaxe")
                {
                    isCompleted = true;
                }
            }

            idx++;
        }
    }

    auto CraftStonePickaxeQuest::getStatus() const -> std::string
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

    auto CraftStoneBowlQuest::update() -> void
    {
        const auto &playerActions{Player::instance().getPlayerActionsRef()};

        auto idx{0};

        for (const auto &entry : playerActions)
        {
            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Mine && actionFirstArg == "ObjectStone")
            {
                m_stonedMined = true;

                Player::instance().getQuestCompletionPointsRef()["MineStoneFromCraftStoneBowl"] =
                    idx;
            }

            if (action == PlayerActionTypes::Craft)
            {
                if (actionFirstArg == "ObjectStoneBowl")
                {
                    isCompleted = true;
                }
            }

            idx++;
        }
    }

    auto CraftStoneBowlQuest::getStatus() const -> std::string
    {
        if (!m_stonedMined)
        {
            return "Mine a stone.";
        }

        return "Craft a stone bowl out of the stone.";
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
            if (idx <= previousBranchPickQuestCompletionPoint)
            {
                idx++;

                continue;
            }

            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Pick && actionFirstArg == "ObjectBranch")
            {
                ++numPickedBranches;
            }

            if (action == PlayerActionTypes::Craft)
            {
                if (actionFirstArg == "ObjectUnlitCampfire")
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
        if (m_numBranchesLeft > 0)
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
            if (idx <= previousMineQuestCompletionPoint)
            {
                idx++;

                continue;
            }

            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Mine && actionFirstArg == "ObjectStone")
            {
                numMinedStones++;

                if (numMinedStones == k_numStonesNeeded)
                {
                    Player::instance().getQuestCompletionPointsRef()["MineStoneFromBoulderQuest1"] =
                        idx;

                    break;
                }
            }

            idx++;
        }

        m_numMinedStonesLeft = k_numStonesNeeded - numMinedStones;

        if (numMinedStones >= k_numStonesNeeded)
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

            if (action == PlayerActionTypes::Craft)
            {
                if (actionFirstArg == "ObjectStoneSlab")
                {
                    numCraftedSlabs++;
                }
            }
        }

        m_numCraftedSlabsLeft = k_numSlabsNeeded - numCraftedSlabs;

        if (numCraftedSlabs >= k_numSlabsNeeded)
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

            if (action == PlayerActionTypes::Lay)
            {
                numLaidSlabs++;
            }
        }

        m_numLaidSlabsLeft = k_numSlabsPlacedNeeded - numLaidSlabs;

        if (numLaidSlabs >= k_numSlabsPlacedNeeded)
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
            if (idx <= previousMineQuestCompletionPoint)
            {
                idx++;
                continue;
            }

            auto action{get<0>(entry)};
            auto actionFirstArg{get<1>(entry)};
            // auto actionSecondArg{get<2>(entry)};

            if (action == PlayerActionTypes::Mine && actionFirstArg == "ObjectStone")
            {
                numMinedStones++;
            }

            idx++;
        }

        m_numMinedStonesLeft = k_numMinedStonesNeeded - numMinedStones;

        if (numMinedStones >= k_numMinedStonesNeeded)
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

            if (action == PlayerActionTypes::Craft)
            {
                if (actionFirstArg == "ObjectStoneBrick")
                {
                    numCraftedBricks++;
                }
            }
        }

        m_numCraftedBricksLeft = k_numCraftedBricksNeeded - numCraftedBricks;

        if (numCraftedBricks >= k_numCraftedBricksNeeded)
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

            if (action == PlayerActionTypes::Craft &&
                (actionFirstArg == "ObjectStoneWall" || actionFirstArg == "ObjectStoneWallDoor"))
            {
                wallPositions.insert({actionSecondArg.x, actionSecondArg.y});
            }
        }

        auto numIncompleteWallTiles{BuildStoneWallsQuest::getNumIncompleteWallTiles(wallPositions)};

        if (!wallPositions.empty() && numIncompleteWallTiles == 0)
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
        auto numIncompleteWallTiles{0};

        auto worldArea{World::instance().getCurrentWorldArea()};

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
                if (tile && tile->getGround() == hash("GroundStoneSlab"))
                {
                    adjacentStoneSlabTiles++;
                }
            }

            auto adjacentStoneWallOrDoorTiles{0};

            for (const auto &tile : tilesWithoutDiagonals)
            {
                if (tile && (tile->getObjectsStack()->countHasObject("ObjectStoneWall") > 0 ||
                             tile->getObjectsStack()->countHasObject("ObjectStoneWallDoor") > 0))
                {
                    adjacentStoneWallOrDoorTiles++;
                }
            }

            if (adjacentStoneSlabTiles < 1 || adjacentStoneWallOrDoorTiles < 2)
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

    auto PlaceSpouseQuest::update() -> void
    {
    }

    auto PlaceSpouseQuest::getStatus() const -> std::string
    {
        return "Place your spouse in the house.";
    }
}
