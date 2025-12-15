//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#include "Actions.hpp"
#include "GUIChatBox.hpp"
#include "GUIInteractionMenu.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "Player/PlayerActions/PlayerActionTypes.hpp"
#include "Player/PlayerCharacter.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "Tile.hpp"
#include "Update/BattleSystem.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0
{
    static std::map<int, Function<void()>> s_timedActions;

    template <>
    Action GetAction<Hash("ActionStop")>();

    template <>
    Action GetAction<Hash("ActionForage")>();

    template <>
    Action GetAction<Hash("ActionChopTree")>();

    template <>
    Action GetAction<Hash("ActionPickBranch")>();

    template <>
    Action GetAction<Hash("ActionPickStone")>();

    template <>
    Action GetAction<Hash("ActionBuildSimpleShelter")>();

    template <>
    Action GetAction<Hash("ActionClaimLand")>();

    template <>
    Action GetAction<Hash("ActionLayMetalFloor")>();

    template <>
    Action GetAction<Hash("ActionChipStone")>();

    template <>
    Action GetAction<Hash("ActionCraftStonePickaxe")>();

    template <>
    Action GetAction<Hash("ActionCraftStoneSlab")>();

    template <>
    Action GetAction<Hash("ActionLayStoneSlab")>();

    template <>
    Action GetAction<Hash("ActionCraftStoneBrick")>();

    template <>
    Action GetAction<Hash("ActionCraftStoneWall")>();

    template <>
    Action GetAction<Hash("ActionCraftStoneWall")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStone");

                    auto worldArea{_<World>().GetCurrentWorldArea()};

                    auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

                    auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

                    if (tile)
                    {
                        tile->GetObjectsStack()->AddObject("ObjectStoneWall");
                    }

                    _<GUIChatBox>().Print("You craft a stone wall.");

                    _<GameplayCore::PlayerCharacter>().AddExperience(10);

                    _<GameplayCore::PlayerCharacter>().AddPlayerAction(
                        GameplayCore::PlayerActionTypes::Craft, "ObjectStoneWall");
                }};
    }

    template <>
    Action GetAction<Hash("ActionCraftStoneBrick")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStone");

                    inventory.AddObject("ObjectStoneBrick");

                    _<GameplayCore::PlayerCharacter>().AddExperience(10);

                    _<GameplayCore::PlayerCharacter>().AddPlayerAction(
                        GameplayCore::PlayerActionTypes::Craft, "ObjectStoneBrick");

                    _<GUIChatBox>().Print("You craft a stone brick.");
                }};
    }

    template <>
    Action GetAction<Hash("ActionLayStoneSlab")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStoneSlab");

                    auto worldArea{_<World>().GetCurrentWorldArea()};

                    auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

                    auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

                    if (tile)
                    {
                        tile->SetGround(Hash("GroundStoneSlab"));
                    }

                    _<GUIChatBox>().Print("You lay a stone slab.");

                    _<GameplayCore::PlayerCharacter>().AddExperience(10);

                    _<GameplayCore::PlayerCharacter>().AddPlayerAction(
                        GameplayCore::PlayerActionTypes::Lay, "ObjectStoneSlab");
                }};
    }

    template <>
    Action GetAction<Hash("ActionCraftStoneSlab")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStone");

                    inventory.AddObject("ObjectStoneSlab");

                    _<GUIChatBox>().Print("You craft a stone slab.");

                    _<GameplayCore::PlayerCharacter>().AddExperience(10);

                    _<GameplayCore::PlayerCharacter>().AddPlayerAction(
                        GameplayCore::PlayerActionTypes::Craft, "ObjectStoneSlab");
                }};
    }

    template <>
    Action GetAction<Hash("ActionCraftStonePickaxe")>()
    {
        return {
            .groundMatches = {},
            .objectMatches = {},
            .action = []()
            {
                auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                if (inventory.CountHasObject("ObjectBranch") < 1)
                {
                    _<GUIChatBox>().Print("You don't have any branches to craft a stone pickaxe.");

                    return;
                }

                if (inventory.CountHasObject("ObjectStone") < 1)
                {
                    _<GUIChatBox>().Print("You don't have any stones to craft a stone pickaxe.");

                    return;
                }

                inventory.RemoveObject("ObjectBranch");
                inventory.RemoveObject("ObjectStone");

                inventory.AddObject("ObjectStonePickaxe");

                _<GUIChatBox>().Print("You craft a stone pickaxe.");

                _<GameplayCore::PlayerCharacter>().AddExperience(10);

                _<GameplayCore::PlayerCharacter>().AddPlayerAction(
                    GameplayCore::PlayerActionTypes::Craft, "ObjectStonePickaxe");
            }};
    }

    template <>
    Action GetAction<Hash("ActionChipStone")>()
    {
        return {.groundMatches = {},
                .objectMatches = {Hash("ObjectStoneBoulder")},
                .action = []()
                {
                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    // inventory.AddObject("ObjectSmallStones");
                    inventory.AddObject("ObjectStone");

                    _<GUIChatBox>().Print("You chip some stone.");

                    _<GameplayCore::PlayerCharacter>().AddExperience(10);

                    _<GameplayCore::PlayerCharacter>().AddPlayerAction(
                        GameplayCore::PlayerActionTypes::Mine, "ObjectStone");
                }};
    }

    template <>
    Action GetAction<Hash("ActionLayCobbleStone")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    auto numSmallStonesInInventory{inventory.CountHasObject("ObjectSmallStones")};

                    if (numSmallStonesInInventory <= 0)
                    {
                        _<GUIChatBox>().Print("You don't have any small stones to lay.");

                        return;
                    }

                    inventory.RemoveObject("ObjectSmallStones");

                    auto worldArea{_<World>().GetCurrentWorldArea()};

                    auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

                    auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

                    if (tile)
                    {
                        tile->SetGround(Hash("GroundCobbleStone"));
                    }

                    _<GUIChatBox>().Print("You lay some cobble stone.");
                }};
    }

    template <>
    Action GetAction<Hash("ActionLayMetalFloor")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    auto numMetalScrapsInInventory{inventory.CountHasObject("ObjectMetalScrap")};

                    if (numMetalScrapsInInventory <= 0)
                    {
                        _<GUIChatBox>().Print("You don't have any metal scraps to lay.");

                        return;
                    }

                    auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

                    auto worldArea{_<World>().GetCurrentWorldArea()};

                    auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

                    if (tile)
                    {
                        tile->SetGround(Hash("GroundMetalFloor"));

                        inventory.RemoveObject("ObjectMetalScrap");
                    }

                    _<GUIChatBox>().Print("You lay some metal floor.");
                }};
    }

    template <>
    Action GetAction<Hash("ActionPlowLand")>()
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
                        tile->SetGround(Hash("GroundPlowedLand"));
                    }

                    _<GUIChatBox>().Print("You plow the land.");
                }};
    }

    template <>
    Action GetAction<Hash("Pick up")>();

    template <>
    Action GetAction<Hash("Pick up")>()
    {
        return {.groundMatches = {},
                .objectMatches = {},
                .action = []()
                {
                    auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

                    auto worldArea{_<World>().GetCurrentWorldArea()};

                    auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

                    if (tile)
                    {
                        auto objectsStack{tile->GetObjectsStack()};

                        auto object{objectsStack->PopObject()};

                        if (object)
                        {
                            auto &inventory{
                                _<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                            inventory.AddObject(object->GetType());
                        }
                    }
                }};
    }

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
    Action GetAction<Hash("ActionChopTree")>()
    {
        return {.groundMatches = {Hash("GroundGrass")},
                .objectMatches = {},
                .action = []()
                {
                    auto worldArea{_<World>().GetCurrentWorldArea()};

                    auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

                    auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

                    if (tile)
                    {
                        if (tile->GetObjectsStack()->CountHasObject("ObjectFirTree") > 0)
                        {
                            tile->GetObjectsStack()->RemoveOneOfObjectOfType("ObjectFirTree");
                        }
                        else if (tile->GetObjectsStack()->CountHasObject("ObjectBirchTree") > 0)
                        {
                            tile->GetObjectsStack()->RemoveOneOfObjectOfType("ObjectBirchTree");
                        }

                        tile->GetObjectsStack()->AddObject("ObjectFelledTree");
                    }

                    _<GUIChatBox>().Print("You chop down a tree.");
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

                    _<GameplayCore::PlayerCharacter>().AddExperience(10);

                    _<GameplayCore::PlayerCharacter>().AddPlayerAction(
                        GameplayCore::PlayerActionTypes::Forage);
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

                    _<GameplayCore::PlayerCharacter>().AddPlayerAction(
                        GameplayCore::PlayerActionTypes::Pick, "ObjectBranch");
                }};
    }

    template <>
    Action GetAction<Hash("ActionPickStone")>()
    {
        return {.groundMatches = {},
                .objectMatches = {Hash("ObjectStone")},
                .action = []()
                {
                    auto worldArea{_<World>().GetCurrentWorldArea()};

                    auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

                    auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

                    if (tile)
                    {
                        tile->GetObjectsStack()->RemoveOneOfObjectOfType("ObjectStone");
                    }

                    auto &inventory{_<GameplayCore::PlayerCharacter>().GetObjectsInventoryRef()};

                    inventory.AddObject("ObjectStone");

                    _<GUIChatBox>().Print("You picked a stone!");

                    _<GameplayCore::PlayerCharacter>().AddPlayerAction(
                        GameplayCore::PlayerActionTypes::Pick, "ObjectStone");
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