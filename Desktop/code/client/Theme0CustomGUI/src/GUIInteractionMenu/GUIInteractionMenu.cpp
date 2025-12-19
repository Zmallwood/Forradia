/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIInteractionMenu.hpp"
#include "Actions.hpp"
#include "GUIInventoryWindow.hpp"
#include "Mouse/MouseInput.hpp"
#include "Object.hpp"
#include "ObjectsStack.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "SDLDevice.hpp"
#include "TextRenderer.hpp"
#include "Tile.hpp"
#include "Update/TileHovering.hpp"
#include "World.hpp"
#include "WorldArea.hpp"

namespace Forradia::Theme0 {
  auto GUIInteractionMenu::Initialize() -> void {
    this->SetVisible(false);

    for (auto i = 0; i < k_maxNumMenuEntries; i++)
      m_renderIDsMenuEntryStrings.push_back(
          Hash("GUIInteractionMenuEntryString" + std::to_string(i)));
  }

  auto GUIInteractionMenu::BuildMenu() -> void {
    m_entries.clear();

    auto mousePos{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

    // First check if clicked in inventory (or other GUI windows)
    auto rightClickedInInventoryWindow{_<GUIInventoryWindow>().GetBounds().Contains(mousePos)};

    if (rightClickedInInventoryWindow)
      std::cout << "asd\n";

    // If not clicked in inventory, check if clicked tile

    auto hoveredCoordinate{_<TileHovering>().GetHoveredCoordinate()};
    auto worldArea{_<World>().GetCurrentWorldArea()};
    auto worldAreaSize{worldArea->GetSize()};

    m_clickedCoordinate = hoveredCoordinate;

    auto tile{worldArea->GetTile(hoveredCoordinate.x, hoveredCoordinate.y)};

    auto objects{tile->GetObjectsStack()->GetObjects()};

    auto ground{0};

    if (tile) {
      ground = tile->GetGround();
    }

    std::vector<int> objectHashes;

    for (auto &object : objects) {
      auto type{object->GetType()};

      objectHashes.push_back(type);
    }
    this->ShowMenuForTileAndObjects(ground, objectHashes);
  }

  auto GUIInteractionMenu::ShowMenuForTileAndObjects(int groundHash, std::vector<int> objectHashes)
      -> void {

    std::vector<Action> actions{GetAction<Hash("ActionStop")>(),
                                GetAction<Hash("ActionLayCobbleStone")>(),
                                GetAction<Hash("ActionPlowLand")>(),
                                GetAction<Hash("ActionForage")>(),
                                GetAction<Hash("ActionCraftStonePickaxe")>(),
                                GetAction<Hash("ActionCraftStoneSlab")>(),
                                GetAction<Hash("ActionLayStoneSlab")>(),
                                GetAction<Hash("ActionCraftStoneBrick")>(),
                                GetAction<Hash("ActionCraftStoneWall")>(),
                                GetAction<Hash("ActionCraftStoneWallDoor")>(),
                                GetAction<Hash("ActionCraftStoneBowl")>(),
                                GetAction<Hash("ActionPickBranch")>(),
                                GetAction<Hash("ActionPickStone")>(),
                                GetAction<Hash("ActionChipStone")>()};

    auto &inventory{_<Player>().GetObjectsInventoryRef()};
    for (auto &action : actions) {
      bool goOn{false};
      for (auto groundMatch : action.groundMatches) {
        if (groundMatch == groundHash) {
          goOn = true;
        }
      }
      if (action.groundMatches.size() == 0) {
        goOn = true;
      }
      if (!goOn)
        continue;
      goOn = false;
      for (auto objectMatch : action.objectMatches) {
        for (auto objectHash : objectHashes) {
          if (objectMatch == objectHash)
            goOn = true;
        }
      }
      if (action.objectMatches.size() == 0)
        goOn = true;
      if (!goOn)
        continue;
      goOn = false;
      for (auto invObjectMatch : action.objectsInInventory) {
        if (inventory.CountHasObject(invObjectMatch)) {
          goOn = true;
        }
      }
      if (action.objectsInInventory.size() == 0)
        goOn = true;

      if (goOn)
        m_entries.push_back({action.label, action.action});
    }

    //    auto actionStop{GetAction<Hash("ActionStop")>()};
    //    m_entries.push_back({"Stop current action", actionStop.action});
    //
    //    //    auto actionPickUp{GetAction<Hash("Pick up")>()};
    //    //    m_entries.push_back({"Pick up", actionPickUp.action});
    //
    //    for (auto objectType : objectHashes) {
    //      auto actionLayCobbleStone{GetAction<Hash("ActionLayCobbleStone")>()};
    //      m_entries.push_back({"Lay cobble stone", actionLayCobbleStone.action});
    //
    //      //      auto actionClaimLand{GetAction<Hash("ActionClaimLand")>()};
    //      //      m_entries.push_back({"Claim land", actionClaimLand.action});
    //
    //      auto actionPlowLand{GetAction<Hash("ActionPlowLand")>()};
    //      m_entries.push_back({"Plow land", actionPlowLand.action});
    //
    //      auto actionForage{GetAction<Hash("ActionForage")>()};
    //
    //      if (!actionForage.groundMatches.empty() && groundHash == actionForage.groundMatches[0])
    //        m_entries.push_back({"Forage", actionForage.action});
    //
    //      auto actionCraftStonePickaxe{GetAction<Hash("ActionCraftStonePickaxe")>()};
    //      m_entries.push_back({"Craft stone pickaxe", actionCraftStonePickaxe.action});
    //
    //      auto actionCraftStoneSlab{GetAction<Hash("ActionCraftStoneSlab")>()};
    //      m_entries.push_back({"Craft stone slab", actionCraftStoneSlab.action});
    //
    //      auto actionLayStoneSlab{GetAction<Hash("ActionLayStoneSlab")>()};
    //      m_entries.push_back({"Lay stone slab", actionLayStoneSlab.action});
    //
    //      auto actionCraftStoneBrick{GetAction<Hash("ActionCraftStoneBrick")>()};
    //      m_entries.push_back({"Craft stone brick", actionCraftStoneBrick.action});
    //
    //      auto actionCraftStoneWall{GetAction<Hash("ActionCraftStoneWall")>()};
    //      m_entries.push_back({"Craft stone wall", actionCraftStoneWall.action});
    //
    //      auto actionCraftStoneWallDoor{GetAction<Hash("ActionCraftStoneWallDoor")>()};
    //      m_entries.push_back({"Craft stone wall door", actionCraftStoneWallDoor.action});
    //
    //      auto actionCraftStoneBowl{GetAction<Hash("ActionCraftStoneBowl")>()};
    //      m_entries.push_back({"Craft stone bowl", actionCraftStoneBowl.action});
    //
    //      auto actionPickBranch{GetAction<Hash("ActionPickBranch")>()};
    //
    //      for (const auto &actionObjectTypes : actionPickBranch.objectMatches) {
    //        if (objectType == actionObjectTypes) {
    //          m_entries.push_back({"Pick branch", actionPickBranch.action});
    //          break;
    //        }
    //      }
    //
    //      auto actionPickStone{GetAction<Hash("ActionPickStone")>()};
    //
    //      for (const auto &actionObjectTypes : actionPickStone.objectMatches) {
    //        if (objectType == actionObjectTypes) {
    //          m_entries.push_back({"Pick stone", actionPickStone.action});
    //          break;
    //        }
    //      }
    //
    //      auto actionChipStone{GetAction<Hash("ActionChipStone")>()};
    //
    //      for (const auto &actionObjectTypes : actionChipStone.objectMatches) {
    //        if (objectType == actionObjectTypes) {
    //          m_entries.push_back({"Chip stone", actionChipStone.action});
    //          break;
    //        }
    //      }
    //    }
  }

  auto GUIInteractionMenu::UpdateDerived() -> void {
    GUIPanel::UpdateDerived();

    auto newHeight{2 * 0.01f + k_lineHeight * (m_entries.size() + 1)};
    this->SetHeight(newHeight);

    auto bounds{this->GetBounds()};
    auto mousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};

    auto i{0};

    for (auto &entry : m_entries) {
      auto menuEntryRect{RectF{bounds.x + 0.01f + k_indentWidth,
                               bounds.y + 0.01f + k_lineHeight * (i + 1), bounds.width,
                               k_lineHeight}};

      if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFired()) {
        if (menuEntryRect.Contains(mousePosition))
          entry.GetAction()();
        this->SetVisible(false);
      }
      ++i;
    }
    if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFiredPickResult())
      this->SetVisible(false);
  }

  auto GUIInteractionMenu::RenderDerived() const -> void {
    GUIPanel::RenderDerived();

    auto bounds{this->GetBounds()};

    _<TextRenderer>().DrawString(k_renderIDActionsString, "Actions", bounds.x + 0.01f,
                                 bounds.y + 0.01f, FontSizes::_20, false, true,
                                 Palette::GetColor<Hash("YellowTransparent")>());
    auto i{0};
    for (auto &entry : m_entries) {
      _<TextRenderer>().DrawString(
          m_renderIDsMenuEntryStrings[i], entry.GetLabel(), bounds.x + 0.01f + k_indentWidth,
          bounds.y + 0.01f + (i + 1) * k_lineHeight, FontSizes::_20, false, true);
      ++i;
    }
  }
}
