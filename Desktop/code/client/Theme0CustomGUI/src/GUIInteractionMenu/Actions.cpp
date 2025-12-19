/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "Actions.hpp"
#include "GUIChatBox.hpp"
#include "GUIInteractionMenu.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerActions/PlayerActionTypes.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "Tile.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
  static std::unordered_map<int, std::function<void()>> s_timedActions;

  template <>
  auto GetAction<Hash("ActionCraftStoneBowl")>() -> Action {
    return {
        .label = "Craft stone bowl",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {Hash("ObjectStone")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.RemoveObject("ObjectStone");

          inventory.AddObject("ObjectStoneBowl");

          _<GUIChatBox>().Print("You craft a stone bowl.");
          _<Player>().AddExperience(10);
          _<Player>().AddPlayerAction(PlayerActionTypes::Craft, "ObjectStoneBowl");
        }};
  }

  template <>
  auto GetAction<Hash("ActionCraftStoneWallDoor")>() -> Action {
    return {
        .label = "Craft stone wall door",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {Hash("ObjectStoneBrick")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.RemoveObject("ObjectStoneBrick");

          auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

          if (tile)
            tile->GetObjectsStack()->AddObject("ObjectStoneWallDoor");

          _<GUIChatBox>().Print("You craft a stone wall door.");
          _<Player>().AddExperience(10);
          _<Player>().AddPlayerAction(PlayerActionTypes::Craft, "ObjectStoneWallDoor",
                                      clickedCoordinate);
        }};
  }

  template <>
  auto GetAction<Hash("ActionCraftStoneWall")>() -> Action {
    return {
        .label = "Craft stone wall",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {Hash("ObjectStoneBrick")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.RemoveObject("ObjectStoneBrick");

          auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

          if (tile)
            tile->GetObjectsStack()->AddObject("ObjectStoneWall");

          _<GUIChatBox>().Print("You craft a stone wall.");
          _<Player>().AddExperience(10);
          _<Player>().AddPlayerAction(PlayerActionTypes::Craft, "ObjectStoneWall",
                                      clickedCoordinate);
        }};
  }

  template <>
  auto GetAction<Hash("ActionCraftStoneBrick")>() -> Action {
    return {
        .label = "Craft stone brick",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {Hash("ObjectStone")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.RemoveObject("ObjectStone");
          inventory.AddObject("ObjectStoneBrick");

          _<Player>().AddExperience(10);
          _<Player>().AddPlayerAction(PlayerActionTypes::Craft, "ObjectStoneBrick");
          _<GUIChatBox>().Print("You craft a stone brick.");
        }};
  }

  template <>
  auto GetAction<Hash("ActionLayStoneSlab")>() -> Action {
    return {
        .label = "Lay stone slab",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {Hash("ObjectStoneSlab")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.RemoveObject("ObjectStoneSlab");

          auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

          if (tile)
            tile->SetGround(Hash("GroundStoneSlab"));

          _<GUIChatBox>().Print("You lay a stone slab.");
          _<Player>().AddExperience(10);
          _<Player>().AddPlayerAction(PlayerActionTypes::Lay, "ObjectStoneSlab");
        }};
  }

  template <>
  auto GetAction<Hash("ActionCraftStoneSlab")>() -> Action {
    return {
        .label = "Craft stone slab",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {Hash("ObjectStone")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.RemoveObject("ObjectStone");
          inventory.AddObject("ObjectStoneSlab");

          _<GUIChatBox>().Print("You craft a stone slab.");
          _<Player>().AddExperience(10);
          _<Player>().AddPlayerAction(PlayerActionTypes::Craft, "ObjectStoneSlab");
        }};
  }

  template <>
  auto GetAction<Hash("ActionCraftStonePickaxe")>() -> Action {
    return {
        .label = "Craft stone pickaxe",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {Hash("ObjectBranch"), Hash("ObjectStone")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          if (inventory.CountHasObject("ObjectBranch") < 1) {
            _<GUIChatBox>().Print("You don't have any branches to craft a stone pickaxe.");
            return;
          }

          if (inventory.CountHasObject("ObjectStone") < 1) {
            _<GUIChatBox>().Print("You don't have any stones to craft a stone pickaxe.");
            return;
          }

          inventory.RemoveObject("ObjectBranch");
          inventory.RemoveObject("ObjectStone");
          inventory.AddObject("ObjectStonePickaxe");

          _<GUIChatBox>().Print("You craft a stone pickaxe.");
          _<Player>().AddExperience(10);
          _<Player>().AddPlayerAction(PlayerActionTypes::Craft, "ObjectStonePickaxe");
        }};
  }

  template <>
  auto GetAction<Hash("ActionChipStone")>() -> Action {
    return {
        .label = "Chip stone",
        .groundMatches = {},
        .objectMatches = {Hash("ObjectStoneBoulder")},
        .objectsInInventory = {Hash("ObjectStonePickaxe")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.AddObject("ObjectStone");

          _<GUIChatBox>().Print("You chip some stone.");
          _<Player>().AddExperience(10);
          _<Player>().AddPlayerAction(PlayerActionTypes::Mine, "ObjectStone");
        }};
  }

  template <>
  auto GetAction<Hash("ActionLayCobbleStone")>() -> Action {
    return {
        .label = "Lay cobble stone",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {Hash("ObjectSmallStones")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          auto numSmallStonesInInventory{inventory.CountHasObject("ObjectSmallStones")};

          if (numSmallStonesInInventory <= 0) {
            _<GUIChatBox>().Print("You don't have any small stones to lay.");
            return;
          }

          inventory.RemoveObject("ObjectSmallStones");

          auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

          if (tile)
            tile->SetGround(Hash("GroundCobbleStone"));

          _<GUIChatBox>().Print("You lay some cobble stone.");
        }};
  }

  template <>
  auto GetAction<Hash("ActionPlowLand")>() -> Action {
    return {
        .label = "Plow land",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {Hash("ObjectPlow")},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

          if (tile)
            tile->SetGround(Hash("GroundPlowedLand"));

          _<GUIChatBox>().Print("You plow the land.");
        }};
  }
  //
  //  template <>
  //  auto GetAction<Hash("Pick up")>() -> Action {
  //    return {.groundMatches = {}, .objectMatches = {}, .objectsInInventory = {}, .action = []() {
  //              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
  //              auto worldArea{_<World>().GetCurrentWorldArea()};
  //              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};
  //
  //              if (tile) {
  //                auto objectsStack{tile->GetObjectsStack()};
  //                auto object{objectsStack->PopObject()};
  //
  //                if (object) {
  //                  auto &inventory{_<Player>().GetObjectsInventoryRef()};
  //                  inventory.AddObject(object->GetType());
  //                }
  //              }
  //            }};
  //  }

  // template <>
  // auto GetAction<Hash("ActionClaimLand")>() -> Action {
  //   return {.groundMatches = {}, .objectMatches = {}, .objectsInInventory = {}, .action = []() {
  //             auto worldArea{_<World>().GetCurrentWorldArea()};
  //             auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
  //             auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

  //            if (tile) {
  //              tile->GetObjectsStack()->AddObject("ObjectLandClaimBanner");

  //              for (auto y = clickedCoordinate.y - 3; y <= clickedCoordinate.y + 3; y++)
  //                for (auto x = clickedCoordinate.x - 3; x <= clickedCoordinate.x + 3; x++)
  //                  worldArea->AddClaimedCoordinate({x, y});
  //            }

  //            _<GUIChatBox>().Print("You claim land.");
  //          }};
  //}

  template <>
  auto GetAction<Hash("ActionStop")>() -> Action {
    return {
        .label = "Stop",
        .groundMatches = {},
        .objectMatches = {},
        .objectsInInventory = {},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          s_timedActions.clear();

          _<GUIChatBox>().Print("You stopped current action.");
        }};
  }

  template <>
  auto GetAction<Hash("ActionForage")>() -> Action {
    return {
        .label = "Forage",
        .groundMatches = {Hash("GroundGrass")},
        .objectMatches = {},
        .objectsInInventory = {},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.AddObject("ObjectBlueberries");

          _<GUIChatBox>().Print("Foraging... You found some "
                                "blueberries!");
          _<Player>().AddExperience(10);
          _<Player>().AddPlayerAction(PlayerActionTypes::Forage);
        }};
  }

  template <>
  auto GetAction<Hash("ActionPickBranch")>() -> Action {
    return {
        .label = "Pick branch",
        .groundMatches = {},
        .objectMatches = {Hash("ObjectFirTree"), Hash("ObjectBirchTree")},
        .objectsInInventory = {},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.AddObject("ObjectBranch");

          _<GUIChatBox>().Print("You picked a branch!");
          _<Player>().AddPlayerAction(PlayerActionTypes::Pick, "ObjectBranch");
        }};
  }

  template <>
  auto GetAction<Hash("ActionPickStone")>() -> Action {
    return {
        .label = "Pick stone",
        .groundMatches = {},
        .objectMatches = {Hash("ObjectStone")},
        .objectsInInventory = {},
        .action = [](std::shared_ptr<Tile> tile, std::vector<std::shared_ptr<Object> *> objects) {
          auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};

          if (tile)
            tile->GetObjectsStack()->RemoveOneOfObjectOfType("ObjectStone");

          auto &inventory{_<Player>().GetObjectsInventoryRef()};

          inventory.AddObject("ObjectStone");

          _<GUIChatBox>().Print("You picked a stone!");
          _<Player>().AddPlayerAction(PlayerActionTypes::Pick, "ObjectStone");
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
