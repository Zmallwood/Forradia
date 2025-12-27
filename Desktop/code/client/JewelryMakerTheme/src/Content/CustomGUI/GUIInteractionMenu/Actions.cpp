/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "Actions.hpp"

#include "Content/CustomGUI/GUIContainerWindow/GUIContainerWindow.hpp"
#include "Content/Essentials/Player/Player.hpp"
#include "Content/Essentials/Player/PlayerActionTypes.hpp"
#include "Content/Essentials/Player/PlayerObjectsInventory.hpp"
#include "Content/WorldStructure/Object.hpp"
#include "Content/WorldStructure/ObjectsStack.hpp"
#include "Content/WorldStructure/Tile.hpp"
#include "ForradiaEngine/GUICore/GUI.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"
#include "ForradiaEngine/ScenesCore.hpp"
#include "GUIInteractionMenu.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    static std::unordered_map<int, std::function<void()>> s_timedActions;

    template <>
    auto getAction<hash("ActionBuildMineEntrance")>() -> Action
    {
        return {.label = "Build mine entrance",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectShovel")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    tile->getObjectsStack()->addObject("ObjectMineEntrance");

                    GUIChatBox::instance().print("You build a mine entrance.");
                }};
    }
    template <>
    auto getAction<hash("ActionLightUnlitCampfire")>() -> Action
    {
        return {.label = "Light campfire",
                .groundMatches = {},
                .objectMatches = {hash("ObjectUnlitCampfire")},
                .objectsInInventory = {},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    for (const auto &object : objects)
                    {
                        if ((*object)->getType() == hash("ObjectUnlitCampfire"))
                        {
                            (*object)->setType(hash("ObjectLitCampfire"));

                            GUIChatBox::instance().print("You light the campfire.");

                            break;
                        }
                    }
                }};
    }

    template <>
    auto getAction<hash("ActionOpenCampfire")>() -> Action
    {
        return {.label = "Open campfire",
                .groundMatches = {},
                .objectMatches = {hash("ObjectUnlitCampfire"), hash("ObjectLitCampfire")},
                .objectsInInventory = {},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    for (const auto &object : objects)
                    {
                        if ((*object)->getType() == hash("ObjectUnlitCampfire") ||
                            (*object)->getType() == hash("ObjectLitCampfire"))
                        {
                            // NOLINTNEXTLINE(readability-qualified-auto)
                            auto mainScene{SceneManager::instance().getScene("MainScene")};

                            auto gui{mainScene->getGUI()};

                            auto containerWindow{std::make_shared<GUIContainerWindow>(
                                *(*object)->getContainedObjects())};

                            containerWindow->setVisible(true);

                            gui->addChildComponent(containerWindow);

                            GUIChatBox::instance().print("You open the campfire.");

                            break;
                        }
                    }
                }};
    }

    template <>
    auto getAction<hash("ActionCraftUnlitCampfire")>() -> Action
    {
        return {.label = "Craft campfire",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectBranch")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    auto numBranchesInInventory{inventory.countHasObject("ObjectBranch")};

                    constexpr auto k_numBranchesRequired{8};

                    if (numBranchesInInventory < k_numBranchesRequired)
                    {
                        GUIChatBox::instance().print("You need 8 branches to craft a campfire.");
                    }
                    else
                    {
                        tile->getObjectsStack()->addObject("ObjectUnlitCampfire");

                        inventory.removeObject("ObjectBranch", k_numBranchesRequired);

                        GUIChatBox::instance().print("You craft a campfire.");

                        // NOLINTNEXTLINE(readability-magic-numbers)
                        Player::instance().addExperience(10);
                        Player::instance().addPlayerAction(PlayerActionTypes::Craft,
                                                           "ObjectUnlitCampfire");
                    }
                }};
    }

    template <>
    auto getAction<hash("ActionOpenStoneBowl")>() -> Action
    {
        return {.label = "Open stone bowl",
                .groundMatches = {},
                .objectMatches = {hash("ObjectStoneBowl")},
                .objectsInInventory = {},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    for (const auto &object : objects)
                    {
                        if ((*object)->getType() == hash("ObjectStoneBowl"))
                        {
                            // NOLINTNEXTLINE(readability-qualified-auto)
                            auto mainScene{SceneManager::instance().getScene("MainScene")};

                            auto gui{mainScene->getGUI()};

                            auto containerWindow{std::make_shared<GUIContainerWindow>(
                                *(*object)->getContainedObjects())};

                            containerWindow->setVisible(true);

                            gui->addChildComponent(containerWindow);

                            GUIChatBox::instance().print("You open the stone bowl.");

                            break;
                        }
                    }
                }};
    }

    template <>
    auto getAction<hash("ActionEatRedApple")>() -> Action
    {
        return {.label = "Eat",
                .groundMatches = {},
                .objectMatches = {hash("ObjectRedApple")},
                .objectsInInventory = {},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    // NOLINTNEXTLINE(readability-qualified-auto)
                    for (const auto &objPtr : objects)
                    {
                        if ((*objPtr)->getType() == hash("ObjectRedApple"))
                        {
                        }
                    }
                    GUIChatBox::instance().print("You eat a red apple.");
                }};
    }

    template <>
    auto getAction<hash("ActionCraftStoneBowl")>() -> Action
    {
        return {.label = "Craft stone bowl",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectStone")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.removeObject("ObjectStone");

                    inventory.addObject("ObjectStoneBowl");

                    GUIChatBox::instance().print("You craft a stone bowl.");

                    // NOLINTNEXTLINE(readability-magic-numbers)
                    Player::instance().addExperience(10);
                    Player::instance().addPlayerAction(PlayerActionTypes::Craft, "ObjectStoneBowl");
                }};
    }

    template <>
    auto getAction<hash("ActionCraftStoneWallDoor")>() -> Action
    {
        return {.label = "Craft stone wall door",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectStoneBrick")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.removeObject("ObjectStoneBrick");

                    auto clickedCoordinate{GUIInteractionMenu::instance().getClickedCoordinate()};

                    if (tile)
                    {
                        tile->getObjectsStack()->addObject("ObjectStoneWallDoor");
                    }

                    GUIChatBox::instance().print("You craft a stone wall door.");

                    // NOLINTNEXTLINE(readability-magic-numbers)
                    Player::instance().addExperience(10);
                    Player::instance().addPlayerAction(PlayerActionTypes::Craft,
                                                       "ObjectStoneWallDoor", clickedCoordinate);
                }};
    }

    template <>
    auto getAction<hash("ActionCraftStoneWall")>() -> Action
    {
        return {.label = "Craft stone wall",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectStoneBrick")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.removeObject("ObjectStoneBrick");

                    auto clickedCoordinate{GUIInteractionMenu::instance().getClickedCoordinate()};

                    if (tile)
                    {
                        tile->getObjectsStack()->addObject("ObjectStoneWall");
                    }

                    GUIChatBox::instance().print("You craft a stone wall.");

                    // NOLINTNEXTLINE(readability-magic-numbers)
                    Player::instance().addExperience(10);
                    Player::instance().addPlayerAction(PlayerActionTypes::Craft, "ObjectStoneWall",
                                                       clickedCoordinate);
                }};
    }

    template <>
    auto getAction<hash("ActionCraftStoneBrick")>() -> Action
    {
        return {.label = "Craft stone brick",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectStone")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.removeObject("ObjectStone");
                    inventory.addObject("ObjectStoneBrick");

                    // NOLINTNEXTLINE(readability-magic-numbers)
                    Player::instance().addExperience(10);
                    Player::instance().addPlayerAction(PlayerActionTypes::Craft,
                                                       "ObjectStoneBrick");

                    GUIChatBox::instance().print("You craft a stone brick.");
                }};
    }

    template <>
    auto getAction<hash("ActionLayStoneSlab")>() -> Action
    {
        return {.label = "Lay stone slab",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectStoneSlab")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.removeObject("ObjectStoneSlab");

                    if (tile)
                    {
                        tile->setGround(hash("GroundStoneSlab"));
                    }

                    GUIChatBox::instance().print("You lay a stone slab.");

                    // NOLINTNEXTLINE(readability-magic-numbers)
                    Player::instance().addExperience(10);
                    Player::instance().addPlayerAction(PlayerActionTypes::Lay, "ObjectStoneSlab");
                }};
    }

    template <>
    auto getAction<hash("ActionCraftStoneSlab")>() -> Action
    {
        return {.label = "Craft stone slab",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectStone")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.removeObject("ObjectStone");
                    inventory.addObject("ObjectStoneSlab");

                    GUIChatBox::instance().print("You craft a stone slab.");

                    // NOLINTNEXTLINE(readability-magic-numbers)
                    Player::instance().addExperience(10);
                    Player::instance().addPlayerAction(PlayerActionTypes::Craft, "ObjectStoneSlab");
                }};
    }

    template <>
    auto getAction<hash("ActionCraftStonePickaxe")>() -> Action
    {
        return {.label = "Craft stone pickaxe",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectBranch"), hash("ObjectStone")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    if (inventory.countHasObject("ObjectBranch") < 1)
                    {
                        GUIChatBox::instance().print(
                            "You don't have any branches to craft a stone pickaxe.");

                        return;
                    }

                    if (inventory.countHasObject("ObjectStone") < 1)
                    {
                        GUIChatBox::instance().print(
                            "You don't have any stones to craft a stone pickaxe.");

                        return;
                    }

                    inventory.removeObject("ObjectBranch");
                    inventory.removeObject("ObjectStone");
                    inventory.addObject("ObjectStonePickaxe");

                    GUIChatBox::instance().print("You craft a stone pickaxe.");

                    // NOLINTNEXTLINE(readability-magic-numbers)
                    Player::instance().addExperience(10);
                    Player::instance().addPlayerAction(PlayerActionTypes::Craft,
                                                       "ObjectStonePickaxe");
                }};
    }

    template <>
    auto getAction<hash("ActionMineStone")>() -> Action
    {
        return {.label = "Mine stone",
                .groundMatches = {},
                .objectMatches = {hash("ObjectStoneBoulder")},
                .objectsInInventory = {hash("ObjectStonePickaxe")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.addObject("ObjectStone");

                    GUIChatBox::instance().print("You mine some stone.");

                    // NOLINTNEXTLINE(readability-magic-numbers)
                    Player::instance().addExperience(10);
                    Player::instance().addPlayerAction(PlayerActionTypes::Mine, "ObjectStone");
                }};
    }

    template <>
    auto getAction<hash("ActionLayCobbleStone")>() -> Action
    {
        return {.label = "Lay cobble stone",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {hash("ObjectSmallStones")},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    auto numSmallStonesInInventory{inventory.countHasObject("ObjectSmallStones")};

                    if (numSmallStonesInInventory <= 0)
                    {
                        GUIChatBox::instance().print("You don't have any small stones to lay.");

                        return;
                    }

                    inventory.removeObject("ObjectSmallStones");

                    if (tile)
                    {
                        tile->setGround(hash("GroundCobbleStone"));
                    }

                    GUIChatBox::instance().print("You lay some cobble stone.");
                }};
    }

    template <>
    auto getAction<hash("ActionPlowLand")>() -> Action
    {
        return {.label = "Plow land",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    if (tile)
                    {
                        tile->setGround(hash("GroundPlowedLand"));
                    }

                    GUIChatBox::instance().print("You plow the land.");
                }};
    }

    template <>
    auto getAction<hash("ActionStop")>() -> Action
    {
        return {.label = "Stop",
                .groundMatches = {},
                .objectMatches = {},
                .objectsInInventory = {},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    s_timedActions.clear();

                    GUIChatBox::instance().print("You stopped current action.");
                }};
    }

    template <>
    auto getAction<hash("ActionForage")>() -> Action
    {
        return {.label = "Forage",
                .groundMatches = {hash("GroundGrass")},
                .objectMatches = {},
                .objectsInInventory = {},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.addObject("ObjectBlueberries");

                    GUIChatBox::instance().print("Foraging... You found some "
                                                 "blueberries!");

                    // NOLINTNEXTLINE(readability-magic-numbers)
                    Player::instance().addExperience(10);
                    Player::instance().addPlayerAction(PlayerActionTypes::Forage);
                }};
    }

    template <>
    auto getAction<hash("ActionPickBranch")>() -> Action
    {
        return {.label = "Pick branch",
                .groundMatches = {},
                .objectMatches = {hash("ObjectFirTree"), hash("ObjectBirchTree")},
                .objectsInInventory = {},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.addObject("ObjectBranch");

                    GUIChatBox::instance().print("You picked a branch!");

                    Player::instance().addPlayerAction(PlayerActionTypes::Pick, "ObjectBranch");
                }};
    }

    template <>
    auto getAction<hash("ActionPickStone")>() -> Action
    {
        return {.label = "Pick stone",
                .groundMatches = {},
                .objectMatches = {hash("ObjectStone")},
                .objectsInInventory = {},
                .action = [](const std::shared_ptr<Tile> &tile,
                             const std::vector<std::shared_ptr<Object> *> &objects)
                {
                    if (tile)
                    {
                        tile->getObjectsStack()->removeOneOfObjectOfType("ObjectStone");
                    }

                    auto &inventory{Player::instance().getObjectsInventoryRef()};

                    inventory.addObject("ObjectStone");

                    GUIChatBox::instance().print("You picked a stone!");

                    Player::instance().addPlayerAction(PlayerActionTypes::Pick, "ObjectStone");
                }};
    }

    auto updateActions() -> void
    {
        for (auto it = s_timedActions.begin(); it != s_timedActions.end();)
        {
            if (getTicks() > it->first)
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
