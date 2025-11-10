//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "Actions.hpp"

#include "GUIChatBox.hpp"

#include "GUIInteractionMenu.hpp"

#include "PlayerCharacter.hpp"

#include "ObjectsInventory.hpp"

#include "World.hpp"

#include "WorldArea.hpp"

#include "Tile.hpp"

#include "ObjectsStack.hpp"

#include "Object.hpp"

#include "Update/BattleSystem.hpp"

namespace Forradia::Theme0
{
    static std::map<int, Function<void()>> s_timedActions;

    template <>
    Action GetAction<Hash("ActionStop")>();

    template <>
    Action GetAction<Hash("ActionSitByComputer")>();

    template <>
    Action GetAction<Hash("ActionForage")>();

    template <>
    Action GetAction<Hash("ActionForageContinue")>();

    template <>
    Action GetAction<Hash("ActionChopTrees")>();

    template <>
    Action GetAction<Hash("ActionMoveToClosestTree")>();

    template <>
    Action GetAction<Hash("ActionPickBranch")>();

    template <>
    Action GetAction<Hash("ActionBuildSimpleShelter")>();

    template <>
    Action GetAction<Hash("ActionTargetRobot")>();

    template <>
    Action GetAction<Hash("ActionClaimLand")>();

    template <>
    Action GetAction<Hash("ActionClaimLand")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto worldArea{_<World>().GetCurrentWorldArea()};

                    auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

                    auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

                    if (tile)
                    {
                        tile->GetObjectsStack()->AddObject("ObjectLandClaimBanner");

                        for (auto y = clickedCoordinate.y - 3; y <= clickedCoordinate.y + 3; y++)
                        {
                            for (auto x = clickedCoordinate.x - 3; x <= clickedCoordinate.x + 3;
                                 x++)
                            {
                                worldArea->AddClaimedCoordinate({x, y});
                            }
                        }
                    }

                    _<GUIChatBox>().Print("You claim land.");
                }};
    }

    template <>
    Action GetAction<Hash("ActionStop")>()
    {
        return {.groundMatches = {Hash("GroundGrass")},
                .objectMatches = {},
                .action = []()
                {
                    s_timedActions.clear();

                    _<GUIChatBox>().Print("You stopped current action.");
                }};
    }

    template <>
    Action GetAction<Hash("ActionSitByComputer")>()
    {
        return {.groundMatches = {},
                .objectMatches = {Hash("ObjectComputer")},
                .action = []()
                {
                    _<GUIChatBox>().Print("You sit by the computer.");

                    _<GUIChatBox>().EnableInput();
                }};
    }

    template <>
    Action GetAction<Hash("ActionChopTrees")>()
    {
        return {.groundMatches = {Hash("GroundGrass")},
                .objectMatches = {},
                .action = []()
                {
                    _<GUIChatBox>().Print("You start chopping down trees.");

                    GetAction<Hash("ActionMoveToClosestTree")>().action();
                }};
    }

    template <>
    Action GetAction<Hash("ActionMoveToClosestTree")>()
    {
        return {.groundMatches = {Hash("GroundGrass")},
                .objectMatches = {},
                .action = []()
                {
                    _<GUIChatBox>().Print("You start moving to closest tree.");

                    auto radius{10};

                    auto worldArea{_<World>().GetCurrentWorldArea()};

                    auto playerPos{_<GameplayCore::PlayerCharacter>().GetPosition()};

                    auto worldAreaSize{worldArea->GetSize()};

                    auto minDist{999999};

                    Point closestTree{-1, -1};

                    for (auto y = playerPos.y - radius; y <= playerPos.y + radius; ++y)
                    {
                        for (auto x = playerPos.x - radius; x <= playerPos.x + radius; ++x)
                        {
                            auto dx = x - playerPos.x;
                            auto dy = y - playerPos.y;

                            if (dx * dx + dy * dy <= radius * radius)
                            {
                                auto xCoord{worldAreaSize.width - x + 1};

                                auto yCoord{worldAreaSize.height - y + 1};

                                auto tile{worldArea->GetTile(xCoord, yCoord)};

                                auto objectsStack{tile->GetObjectsStack()};

                                for (auto object : objectsStack->GetObjects())
                                {
                                    if (object->GetType() == Hash("ObjectFirTre"
                                                                  "e") ||
                                        object->GetType() == Hash("ObjectBirchTr"
                                                                  "ee"))
                                    {
                                        auto dist{(x - playerPos.x) * (x - playerPos.x) +
                                                  (y - playerPos.y) * (y - playerPos.y)};

                                        if (dist < minDist)
                                        {
                                            minDist = dist;

                                            closestTree = {x, y};
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (closestTree.x != -1)
                    {
                        _<GameplayCore::PlayerCharacter>().SetDestination(
                            {closestTree.x, closestTree.y});
                    }

                    _<GUIChatBox>().Print("You dont find any "
                                          "tree closeby.");
                }};
    }

    template <>
    Action GetAction<Hash("ActionForage")>()
    {
        return {.groundMatches = {Hash("GroundGrass")},
                .objectMatches = {},
                .action = []()
                {
                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    inventory.AddObject("ObjectBlueberries");

                    _<GUIChatBox>().Print("Foraging... You found some "
                                          "blueberries!");

                    s_timedActions.insert(
                        {GetTicks() + 2000, GetAction<Hash("ActionForageContinue")>().action});
                }};
    }

    template <>
    Action GetAction<Hash("ActionForageContinue")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto direction{GetRandomInt(4)};

                    switch (direction)
                    {
                    case 0:
                        _<GameplayCore::PlayerCharacter>().MoveNorth();
                        break;
                    case 1:
                        _<GameplayCore::PlayerCharacter>().MoveEast();
                        break;
                    case 2:
                        _<GameplayCore::PlayerCharacter>().MoveSouth();
                        break;
                    case 3:
                        _<GameplayCore::PlayerCharacter>().MoveWest();
                        break;
                    }

                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    inventory.AddObject("ObjectBlueberries");

                    _<GUIChatBox>().Print("Continue foraging... You "
                                          "found some blueberries!");

                    s_timedActions.insert(
                        {GetTicks() + 2000, GetAction<Hash("ActionForageContinue")>().action});
                }};
    }

    template <>
    Action GetAction<Hash("ActionPickBranch")>()
    {
        return {.groundMatches = {},
                .objectMatches = {Hash("ObjectFirTree"), Hash("ObjectBirchTree")},
                .action = []()
                {
                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    inventory.AddObject("ObjectBranch");

                    _<GUIChatBox>().Print("You picked a branch!");
                }};
    }

    template <>
    Action GetAction<Hash("ActionBuildSimpleShelter")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    _<GUIChatBox>().Print("You start build a simple "
                                          "shelter.");

                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    auto hasBranchesCount{inventory.CountHasObject("ObjectBranch")};

                    auto requiredBranchesCount{4};

                    auto lackingBranchesCount{requiredBranchesCount - hasBranchesCount};

                    if (lackingBranchesCount <= 0)
                    {
                        _<GUIChatBox>().Print("You finished building a "
                                              "simple "
                                              "shelter.");
                    }
                    else
                    {
                        _<GUIChatBox>().Print("You need " + std::to_string(lackingBranchesCount) +
                                              " more branches to "
                                              "build a simple "
                                              "shelter.");
                    }
                }};
    }

    template <>
    Action GetAction<Hash("ActionTargetRobot")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto robot{_<GUIInteractionMenu>().GetClickedRobot()};

                    if (robot)
                    {
                        _<GameplayCore::BattleSystem>().SetTargetedRobot(robot);

                        _<GUIChatBox>().Print("You start battling a robot.");
                    }
                    else
                    {
                        _<GUIChatBox>().Print("There is no robot to target "
                                              "at that location.");
                    }
                }};
    }

    void UpdateActions()
    {
        for (auto it = s_timedActions.begin(); it != s_timedActions.end();)
        {
            if (GetTicks() > it->first)
            {
                it->second();
                it = s_timedActions.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}
