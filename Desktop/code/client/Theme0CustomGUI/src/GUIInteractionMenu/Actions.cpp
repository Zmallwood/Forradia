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
  auto GetAction<Hash("ActionStop")>() -> Action;

  template <>
  auto GetAction<Hash("ActionForage")>() -> Action;

  template <>
  auto GetAction<Hash("ActionChopTree")>() -> Action;

  template <>
  auto GetAction<Hash("ActionPickBranch")>() -> Action;

  template <>
  auto GetAction<Hash("ActionPickStone")>() -> Action;

  template <>
  auto GetAction<Hash("ActionBuildSimpleShelter")>() -> Action;

  template <>
  auto GetAction<Hash("ActionClaimLand")>() -> Action;

  template <>
  auto GetAction<Hash("ActionLayMetalFloor")>() -> Action;

  template <>
  auto GetAction<Hash("ActionChipStone")>() -> Action;

  template <>
  auto GetAction<Hash("ActionCraftStonePickaxe")>() -> Action;

  template <>
  auto GetAction<Hash("ActionCraftStoneSlab")>() -> Action;

  template <>
  auto GetAction<Hash("ActionLayStoneSlab")>() -> Action;

  template <>
  auto GetAction<Hash("ActionCraftStoneBrick")>() -> Action;

  template <>
  auto GetAction<Hash("ActionCraftStoneWall")>() -> Action;

  template <>
  auto GetAction<Hash("ActionCraftStoneWallDoor")>() -> Action;

  template <>
  auto GetAction<Hash("ActionCraftStoneBowl")>() -> Action;

  template <>
  auto GetAction<Hash("ActionCraftStoneBowl")>() -> Action;

  template <>
  auto GetAction<Hash("ActionCraftStoneBowl")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
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
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
              auto &inventory{_<Player>().GetObjectsInventoryRef()};

              inventory.RemoveObject("ObjectStoneBrick");

              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

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
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
              auto &inventory{_<Player>().GetObjectsInventoryRef()};

              inventory.RemoveObject("ObjectStoneBrick");

              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

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
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
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
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
              auto &inventory{_<Player>().GetObjectsInventoryRef()};

              inventory.RemoveObject("ObjectStoneSlab");

              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

              if (tile)
                tile->SetGround(Hash("GroundStoneSlab"));

              _<GUIChatBox>().Print("You lay a stone slab.");
              _<Player>().AddExperience(10);
              _<Player>().AddPlayerAction(PlayerActionTypes::Lay, "ObjectStoneSlab");
            }};
  }

  template <>
  auto GetAction<Hash("ActionCraftStoneSlab")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
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
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
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
    return {.groundMatches = {}, .objectMatches = {Hash("ObjectStoneBoulder")}, .action = []() {
              auto &inventory{_<Player>().GetObjectsInventoryRef()};

              inventory.AddObject("ObjectStone");

              _<GUIChatBox>().Print("You chip some stone.");
              _<Player>().AddExperience(10);
              _<Player>().AddPlayerAction(PlayerActionTypes::Mine, "ObjectStone");
            }};
  }

  template <>
  auto GetAction<Hash("ActionLayCobbleStone")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
              auto &inventory{_<Player>().GetObjectsInventoryRef()};

              auto numSmallStonesInInventory{inventory.CountHasObject("ObjectSmallStones")};

              if (numSmallStonesInInventory <= 0) {
                _<GUIChatBox>().Print("You don't have any small stones to lay.");
                return;
              }

              inventory.RemoveObject("ObjectSmallStones");

              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

              if (tile)
                tile->SetGround(Hash("GroundCobbleStone"));

              _<GUIChatBox>().Print("You lay some cobble stone.");
            }};
  }

  template <>
  auto GetAction<Hash("ActionLayMetalFloor")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
              auto &inventory{_<Player>().GetObjectsInventoryRef()};

              auto numMetalScrapsInInventory{inventory.CountHasObject("ObjectMetalScrap")};

              if (numMetalScrapsInInventory <= 0) {
                _<GUIChatBox>().Print("You don't have any metal scraps to lay.");
                return;
              }

              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

              if (tile) {
                tile->SetGround(Hash("GroundMetalFloor"));

                inventory.RemoveObject("ObjectMetalScrap");
              }

              _<GUIChatBox>().Print("You lay some metal floor.");
            }};
  }

  template <>
  auto GetAction<Hash("ActionPlowLand")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

              if (tile)
                tile->SetGround(Hash("GroundPlowedLand"));

              _<GUIChatBox>().Print("You plow the land.");
            }};
  }

  template <>
  auto GetAction<Hash("Pick up")>() -> Action;

  template <>
  auto GetAction<Hash("Pick up")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

              if (tile) {
                auto objectsStack{tile->GetObjectsStack()};
                auto object{objectsStack->PopObject()};

                if (object) {
                  auto &inventory{_<Player>().GetObjectsInventoryRef()};
                  inventory.AddObject(object->GetType());
                }
              }
            }};
  }

  template <>
  auto GetAction<Hash("ActionClaimLand")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

              if (tile) {
                tile->GetObjectsStack()->AddObject("ObjectLandClaimBanner");

                for (auto y = clickedCoordinate.y - 3; y <= clickedCoordinate.y + 3; y++)
                  for (auto x = clickedCoordinate.x - 3; x <= clickedCoordinate.x + 3; x++)
                    worldArea->AddClaimedCoordinate({x, y});
              }

              _<GUIChatBox>().Print("You claim land.");
            }};
  }

  template <>
  auto GetAction<Hash("ActionStop")>() -> Action {
    return {.groundMatches = {Hash("GroundGrass")}, .objectMatches = {}, .action = []() {
              s_timedActions.clear();

              _<GUIChatBox>().Print("You stopped current action.");
            }};
  }

  template <>
  auto GetAction<Hash("ActionSitByComputer")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {Hash("ObjectComputer")}, .action = []() {
              _<GUIChatBox>().Print("You sit by the computer.");

              _<GUIChatBox>().EnableInput();
            }};
  }

  template <>
  auto GetAction<Hash("ActionChopTree")>() -> Action {
    return {.groundMatches = {Hash("GroundGrass")}, .objectMatches = {}, .action = []() {
              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

              if (tile) {
                if (tile->GetObjectsStack()->CountHasObject("ObjectFirTree") > 0)
                  tile->GetObjectsStack()->RemoveOneOfObjectOfType("ObjectFirTree");
                else if (tile->GetObjectsStack()->CountHasObject("ObjectBirchTree") > 0)
                  tile->GetObjectsStack()->RemoveOneOfObjectOfType("ObjectBirchTree");

                tile->GetObjectsStack()->AddObject("ObjectFelledTree");
              }

              _<GUIChatBox>().Print("You chop down a tree.");
            }};
  }

  template <>
  auto GetAction<Hash("ActionForage")>() -> Action {
    return {.groundMatches = {Hash("GroundGrass")}, .objectMatches = {}, .action = []() {
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
    return {.groundMatches = {},
            .objectMatches = {Hash("ObjectFirTree"), Hash("ObjectBirchTree")},
            .action = []() {
              auto &inventory{_<Player>().GetObjectsInventoryRef()};

              inventory.AddObject("ObjectBranch");

              _<GUIChatBox>().Print("You picked a branch!");
              _<Player>().AddPlayerAction(PlayerActionTypes::Pick, "ObjectBranch");
            }};
  }

  template <>
  auto GetAction<Hash("ActionPickStone")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {Hash("ObjectStone")}, .action = []() {
              auto worldArea{_<World>().GetCurrentWorldArea()};
              auto clickedCoordinate{_<GUIInteractionMenu>().GetClickedCoordinate()};
              auto tile{worldArea->GetTile(clickedCoordinate.x, clickedCoordinate.y)};

              if (tile)
                tile->GetObjectsStack()->RemoveOneOfObjectOfType("ObjectStone");

              auto &inventory{_<Player>().GetObjectsInventoryRef()};

              inventory.AddObject("ObjectStone");

              _<GUIChatBox>().Print("You picked a stone!");
              _<Player>().AddPlayerAction(PlayerActionTypes::Pick, "ObjectStone");
            }};
  }

  template <>
  auto GetAction<Hash("ActionBuildSimpleShelter")>() -> Action {
    return {.groundMatches = {}, .objectMatches = {}, .action = []() {
              _<GUIChatBox>().Print("You start build a simple "
                                    "shelter.");

              auto &inventory{_<Player>().GetObjectsInventoryRef()};

              auto hasBranchesCount{inventory.CountHasObject("ObjectBranch")};
              auto requiredBranchesCount{4};
              auto lackingBranchesCount{requiredBranchesCount - hasBranchesCount};

              if (lackingBranchesCount <= 0)
                _<GUIChatBox>().Print("You finished building a "
                                      "simple "
                                      "shelter.");
              else
                _<GUIChatBox>().Print("You need " + std::to_string(lackingBranchesCount) +
                                      " more branches to "
                                      "build a simple "
                                      "shelter.");
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
