/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Actions.hpp"
#include "GUI.hpp"
#include "GUIChatBox.hpp"
#include "GUIContainerWindow.hpp"
#include "GUIInteractionMenu.hpp"
#include "IScene.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerActions/PlayerActionTypes.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "SceneManager.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
    static std::unordered_map<int, std::function<void()>> s_timedActions;

    template <>
    auto GetAction<Hash("ActionOpenStoneBowl")>() -> Action {
        return {.label = "Open",
                .groundMatches = {},
                .objectMatches = {Hash("ObjectStoneBowl")},
                .objectsInInventory = {},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    for (auto &object : objects) {
                        if ((*object)->GetType() == Hash("ObjectStoneBowl")) {
                            auto mainScene{SceneManager::Instance().GetScene("MainScene")};
                            auto gui{mainScene->GetGUI()};
                            auto containerWindow{std::make_shared<GUIContainerWindow>(
                                *(*object)->GetContainedObjects())};
                            containerWindow->SetVisible(true);
                            gui->AddChildComponent(containerWindow);
                            GUIChatBox::Instance().Print("You open the stone bowl.");
                            break;
                        }
                    }
                }};
    }

    template <>
    auto GetAction<Hash("ActionEatRedApple")>() -> Action {
        return {.label = "Eat",
                .groundMatches = {},
                .objectMatches = {Hash("ObjectRedApple")},
                .objectsInInventory = {},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    for (auto objPtr : objects) {
                        if ((*objPtr)->GetType() == Hash("ObjectRedApple")) {
                        }
                    }
                    GUIChatBox::Instance().Print("You eat a red apple.");
                    // Player::Instance().AddPlayerAction(PlayerActionTypes::Craft,
                    // "ObjectStoneBowl");
                }};
    }

    template <>
    auto GetAction<Hash("ActionCraftStoneBowl")>() -> Action {
        return {.label = "Craft stone bowl",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {Hash("ObjectStone")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStone");

                    inventory.AddObject("ObjectStoneBowl");

                    GUIChatBox::Instance().Print("You craft a stone bowl.");
                    Player::Instance().AddExperience(10);
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Craft, "ObjectStoneBowl");
                }};
    }

    template <>
    auto GetAction<Hash("ActionCraftStoneWallDoor")>() -> Action {
        return {.label = "Craft stone wall door",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {Hash("ObjectStoneBrick")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStoneBrick");

                    auto clickedCoordinate{GUIInteractionMenu::Instance().GetClickedCoordinate()};

                    if (tile)
                        tile->GetObjectsStack()->AddObject("ObjectStoneWallDoor");

                    GUIChatBox::Instance().Print("You craft a stone wall door.");
                    Player::Instance().AddExperience(10);
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Craft,
                                                       "ObjectStoneWallDoor", clickedCoordinate);
                }};
    }

    template <>
    auto GetAction<Hash("ActionCraftStoneWall")>() -> Action {
        return {.label = "Craft stone wall",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {Hash("ObjectStoneBrick")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStoneBrick");

                    auto clickedCoordinate{GUIInteractionMenu::Instance().GetClickedCoordinate()};

                    if (tile)
                        tile->GetObjectsStack()->AddObject("ObjectStoneWall");

                    GUIChatBox::Instance().Print("You craft a stone wall.");
                    Player::Instance().AddExperience(10);
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Craft, "ObjectStoneWall",
                                                       clickedCoordinate);
                }};
    }

    template <>
    auto GetAction<Hash("ActionCraftStoneBrick")>() -> Action {
        return {.label = "Craft stone brick",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {Hash("ObjectStone")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStone");
                    inventory.AddObject("ObjectStoneBrick");

                    Player::Instance().AddExperience(10);
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Craft,
                                                       "ObjectStoneBrick");
                    GUIChatBox::Instance().Print("You craft a stone brick.");
                }};
    }

    template <>
    auto GetAction<Hash("ActionLayStoneSlab")>() -> Action {
        return {.label = "Lay stone slab",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {Hash("ObjectStoneSlab")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStoneSlab");

                    auto clickedCoordinate{GUIInteractionMenu::Instance().GetClickedCoordinate()};

                    if (tile)
                        tile->SetGround(Hash("GroundStoneSlab"));

                    GUIChatBox::Instance().Print("You lay a stone slab.");
                    Player::Instance().AddExperience(10);
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Lay, "ObjectStoneSlab");
                }};
    }

    template <>
    auto GetAction<Hash("ActionCraftStoneSlab")>() -> Action {
        return {.label = "Craft stone slab",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {Hash("ObjectStone")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.RemoveObject("ObjectStone");
                    inventory.AddObject("ObjectStoneSlab");

                    GUIChatBox::Instance().Print("You craft a stone slab.");
                    Player::Instance().AddExperience(10);
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Craft, "ObjectStoneSlab");
                }};
    }

    template <>
    auto GetAction<Hash("ActionCraftStonePickaxe")>() -> Action {
        return {.label = "Craft stone pickaxe",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {Hash("ObjectBranch"), Hash("ObjectStone")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    if (inventory.CountHasObject("ObjectBranch") < 1) {
                        GUIChatBox::Instance().Print(
                            "You don't have any branches to craft a stone pickaxe.");
                        return;
                    }

                    if (inventory.CountHasObject("ObjectStone") < 1) {
                        GUIChatBox::Instance().Print(
                            "You don't have any stones to craft a stone pickaxe.");
                        return;
                    }

                    inventory.RemoveObject("ObjectBranch");
                    inventory.RemoveObject("ObjectStone");
                    inventory.AddObject("ObjectStonePickaxe");

                    GUIChatBox::Instance().Print("You craft a stone pickaxe.");
                    Player::Instance().AddExperience(10);
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Craft,
                                                       "ObjectStonePickaxe");
                }};
    }

    template <>
    auto GetAction<Hash("ActionMineStone")>() -> Action {
        return {.label = "Mine stone",
                .groundMatches = {},
                .objectMatches = {Hash("ObjectStoneBoulder")},
                .objectsInInventory = {Hash("ObjectStonePickaxe")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.AddObject("ObjectStone");

                    GUIChatBox::Instance().Print("You mine some stone.");
                    Player::Instance().AddExperience(10);
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Mine, "ObjectStone");
                }};
    }

    template <>
    auto GetAction<Hash("ActionLayCobbleStone")>() -> Action {
        return {.label = "Lay cobble stone",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {Hash("ObjectSmallStones")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    auto numSmallStonesInInventory{inventory.CountHasObject("ObjectSmallStones")};

                    if (numSmallStonesInInventory <= 0) {
                        GUIChatBox::Instance().Print("You don't have any small stones to lay.");
                        return;
                    }

                    inventory.RemoveObject("ObjectSmallStones");

                    auto clickedCoordinate{GUIInteractionMenu::Instance().GetClickedCoordinate()};

                    if (tile)
                        tile->SetGround(Hash("GroundCobbleStone"));

                    GUIChatBox::Instance().Print("You lay some cobble stone.");
                }};
    }

    template <>
    auto GetAction<Hash("ActionPlowLand")>() -> Action {
        return {.label = "Plow land",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {Hash("ObjectPlow")},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto clickedCoordinate{GUIInteractionMenu::Instance().GetClickedCoordinate()};

                    if (tile)
                        tile->SetGround(Hash("GroundPlowedLand"));

                    GUIChatBox::Instance().Print("You plow the land.");
                }};
    }

    template <>
    auto GetAction<Hash("ActionStop")>() -> Action {
        return {.label = "Stop",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    s_timedActions.clear();

                    GUIChatBox::Instance().Print("You stopped current action.");
                }};
    }

    template <>
    auto GetAction<Hash("ActionForage")>() -> Action {
        return {.label = "Forage",
                .groundMatches = {Hash("GroundGrass")},
                .objectMatches = {},
                .objectsInInventory = {},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.AddObject("ObjectBlueberries");

                    GUIChatBox::Instance().Print("Foraging... You found some "
                                                 "blueberries!");
                    Player::Instance().AddExperience(10);
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Forage);
                }};
    }

    template <>
    auto GetAction<Hash("ActionPickBranch")>() -> Action {
        return {.label = "Pick branch",
                .groundMatches = {},
                .objectMatches = {Hash("ObjectFirTree"), Hash("ObjectBirchTree")},
                .objectsInInventory = {},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.AddObject("ObjectBranch");

                    GUIChatBox::Instance().Print("You picked a branch!");
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Pick, "ObjectBranch");
                }};
    }

    template <>
    auto GetAction<Hash("ActionPickStone")>() -> Action {
        return {.label = "Pick stone",
                .groundMatches = {},
                .objectMatches = {Hash("ObjectStone")},
                .objectsInInventory = {},
                .action = [](std::shared_ptr<Tile> tile,
                             std::vector<std::shared_ptr<Object> *> objects) {
                    auto clickedCoordinate{GUIInteractionMenu::Instance().GetClickedCoordinate()};

                    if (tile)
                        tile->GetObjectsStack()->RemoveOneOfObjectOfType("ObjectStone");

                    auto &inventory{Player::Instance().GetObjectsInventoryRef()};

                    inventory.AddObject("ObjectStone");

                    GUIChatBox::Instance().Print("You picked a stone!");
                    Player::Instance().AddPlayerAction(PlayerActionTypes::Pick, "ObjectStone");
                }};
    }

    auto UpdateActions() -> void {
        for (auto it = s_timedActions.begin(); it != s_timedActions.end();) {
            if (GetTicks() > it->first) {
                it->second();
                it = s_timedActions.erase(it);
            } else {
                ++it;
            }
        }
    }
}
