/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIInteractionMenu.hpp"
#include "Actions.hpp"
#include "Color2DRenderer.hpp"
#include "Cursor.hpp"
#include "GUIChatBox.hpp"
#include "GUIInventoryWindow.hpp"
#include "MouseUtilities.hpp"
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

namespace Forradia::Theme0
{
    auto GUIInteractionMenu::Initialize() -> void
    {
        this->SetVisible(false);

        for (auto i = 0; i < k_maxNumMenuEntries; i++)
        {
            m_renderIDsMenuEntryStrings.push_back(
                Hash("GUIInteractionMenuEntryString" + std::to_string(i)));
        }
    }

    auto GUIInteractionMenu::OnMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        switch (mouseButton)
        {
        case SDL_BUTTON_LEFT:
        {
            if (this->GetVisible())
            {
                this->HandleClick();
                this->SetVisible(false);

                return true;
            }
        }
        break;

        case SDL_BUTTON_RIGHT:
        {
            if (this->GetVisible() == false)
            {
                this->SetVisible(true);
                this->SetPosition(GetNormalizedMousePosition(SDLDevice::Instance().GetWindow()));
                this->BuildMenu();

                return true;
            }
        }
        break;
        default:
            break;
        }

        return false;
    }

    auto GUIInteractionMenu::BuildMenu() -> void
    {
        m_entries.clear();

        auto mousePos{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};

        // First check if clicked in inventory (or other GUI windows)
        auto rightClickedInInventoryWindow{
            GUIInventoryWindow::Instance().GetBounds().Contains(mousePos)};

        if (GUIInventoryWindow::Instance().GetVisible() && rightClickedInInventoryWindow)
        {
            m_clickedCoordinate = {-1, -1};

            m_clickedObjects.clear();

            auto object{GUIInventoryWindow::Instance().GetObjectPtrPtr(mousePos)};

            if (object)
            {
                std::vector<int> objectHashes;

                objectHashes.push_back((*object)->GetType());

                m_clickedObjects.push_back(object.get());

                this->ShowMenuForTileAndObjects(0, objectHashes);

                return;
            }
        }
        // If not clicked in inventory, check if clicked tile

        auto hoveredCoordinate{TileHovering::Instance().GetHoveredCoordinate()};
        auto worldArea{World::Instance().GetCurrentWorldArea()};

        m_clickedCoordinate = hoveredCoordinate;

        auto tile{worldArea->GetTile(hoveredCoordinate.x, hoveredCoordinate.y)};

        auto objects{tile->GetObjectsStack()->GetObjects()};

        auto ground{0};

        if (tile)
        {
            ground = tile->GetGround();
        }

        std::vector<int> objectHashes;

        for (auto &object : objects)
        {
            auto type{object->GetType()};

            objectHashes.push_back(type);
        }

        this->ShowMenuForTileAndObjects(ground, objectHashes);
    }

    auto GUIInteractionMenu::ShowMenuForTileAndObjects(int groundHash,
                                                       const std::vector<int>& objectHashes) -> void
    {
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
                                    GetAction<Hash("ActionMineStone")>(),
                                    GetAction<Hash("ActionEatRedApple")>(),
                                    GetAction<Hash("ActionOpenStoneBowl")>(),
                                    GetAction<Hash("ActionCraftUnlitCampfire")>(),
                                    GetAction<Hash("ActionOpenCampfire")>(),
                                    GetAction<Hash("ActionLightUnlitCampfire")>()};

        auto &inventory{Player::Instance().GetObjectsInventoryRef()};

        for (auto &action : actions)
        {
            bool goOn{false};

            for (auto groundMatch : action.groundMatches)
            {
                if (groundMatch == groundHash)
                {
                    goOn = true;
                }
            }

            if (action.groundMatches.size() == 0 || groundHash == 0)
            {
                goOn = true;
            }

            if (!goOn)
            {
                continue;
            }

            goOn = false;

            for (auto objectMatch : action.objectMatches)
            {
                for (auto objectHash : objectHashes)
                {
                    if (objectMatch == objectHash)
                    {
                        goOn = true;
                    }
                }
            }
            if (action.objectMatches.size() == 0)
            {
                goOn = true;
            }

            if (!goOn)
            {
                continue;
            }

            goOn = false;

            for (auto invObjectMatch : action.objectsInInventory)
            {
                if (inventory.CountHasObject(invObjectMatch))
                {
                    goOn = true;
                }
            }

            if (action.objectsInInventory.size() == 0)
            {
                goOn = true;
            }

            if (goOn)
            {
                m_entries.push_back({action.label, action.action});
            }
        }

        auto newHeight{2 * 0.01f + k_lineHeight * (m_entries.size() + 1)};

        this->SetHeight(newHeight);
    }

    auto GUIInteractionMenu::HandleClick() -> void
    {
        auto bounds{this->GetBounds()};

        auto mousePosition{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};

        auto i{0};

        for (auto &entry : m_entries)
        {
            auto menuEntryRect{RectF{bounds.x + 0.01f + k_indentWidth,
                                     bounds.y + 0.01f + k_lineHeight * (i + 1), bounds.width,
                                     k_lineHeight}};

            if (menuEntryRect.Contains(mousePosition))
            {
                auto worldArea{World::Instance().GetCurrentWorldArea()};

                auto tile{worldArea->GetTile(m_clickedCoordinate)};

                if (tile)
                {
                    auto playerPos{Player::Instance().GetPosition()};

                    auto absDx{std::abs(m_clickedCoordinate.x - playerPos.x)};
                    auto absDy{std::abs(m_clickedCoordinate.y - playerPos.y)};

                    if (absDx > 1 || absDy > 1)
                    {
                        GUIChatBox::Instance().Print("You are too far away to do the action.");

                        this->SetVisible(false);

                        return;
                    }

                    m_clickedObjects.clear();

                    for (auto obj : tile->GetObjectsStack()->GetObjects())
                    {
                        m_clickedObjects.push_back(&obj);
                    }
                }

                entry.GetAction()(tile, m_clickedObjects);
            }

            this->SetVisible(false);

            ++i;
        }

        this->SetVisible(false);
    }

    auto GUIInteractionMenu::UpdateDerived() -> void
    {
        GUIPanel::UpdateDerived();

        auto mousePos{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};

        auto bounds{this->GetBounds()};

        bounds.y += k_lineHeight + 0.01F;

        bounds.height -= k_lineHeight + 2 * 0.01F;

        if (bounds.Contains(mousePos))
        {
            Cursor::Instance().SetCursorStyle(CursorStyles::HoveringClickableGUI);
        }
    }

    auto GUIInteractionMenu::RenderDerived() const -> void
    {
        GUIPanel::RenderDerived();

        auto bounds{this->GetBounds()};

        TextRenderer::Instance().DrawString(k_renderIDActionsString, "Actions", bounds.x + 0.01f,
                                            bounds.y + 0.01f, FontSizes::_20, false, true,
                                            Palette::GetColor<Hash("YellowTransparent")>());

        auto i{0};

        auto mousePos{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};

        for (auto &entry : m_entries)
        {
            auto rowBounds{
                RectF{bounds.x, bounds.y + (i + 1) * k_lineHeight, bounds.width, k_lineHeight}};

            if (rowBounds.Contains(mousePos))
            {
                Color2DRenderer::Instance().DrawFilledRectangle(
                    k_renderIDHoveredRow, Palette::GetColor<Hash("MildBlueTransparent")>(),
                    rowBounds.x, rowBounds.y, rowBounds.width, rowBounds.height, true);
            }

            TextRenderer::Instance().DrawString(
                m_renderIDsMenuEntryStrings[i], entry.GetLabel(), bounds.x + 0.01f + k_indentWidth,
                bounds.y + 0.01f + (i + 1) * k_lineHeight, FontSizes::_20, false, true);

            ++i;
        }
    }
}
