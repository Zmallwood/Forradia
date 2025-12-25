/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIInteractionMenu.hpp"
#include "Actions.hpp"
#include "ForradiaEngine/Rendering/Colors/Color2DRenderer.hpp"
#include "ForradiaEngine/MinorComponents/Cursor.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"
#include "Content/CustomGUI/GUIInventoryWindow.hpp"
#include "ForradiaEngine/Common/Utilities/MouseUtilities.hpp"
#include "Content/WorldStructure/Object.hpp"
#include "Content/WorldStructure/ObjectsStack.hpp"
#include "Content/Essentials/Player/Player.hpp"
#include "Content/Essentials/Player/PlayerObjectsInventory.hpp"
#include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
#include "ForradiaEngine/Rendering/Text/TextRenderer.hpp"
#include "Content/WorldStructure/Tile.hpp"
#include "Content/Core/Update/TileHovering.hpp"
#include "Content/WorldStructure/World.hpp"
#include "Content/WorldStructure/WorldArea.hpp"

namespace Forradia::Theme0
{
    auto GUIInteractionMenu::initialize() -> void
    {
        this->setVisible(false);

        for (auto i = 0; i < k_maxNumMenuEntries; i++)
        {
            m_renderIDsMenuEntryStrings.push_back(
                hash("GUIInteractionMenuEntryString" + std::to_string(i)));
        }
    }

    auto GUIInteractionMenu::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        switch (mouseButton)
        {
        case SDL_BUTTON_LEFT:
        {
            if (this->getVisible())
            {
                this->handleClick();
                this->setVisible(false);

                return true;
            }
        }
        break;

        case SDL_BUTTON_RIGHT:
        {
            if (this->getVisible() == false)
            {
                this->setVisible(true);
                this->setPosition(getNormalizedMousePosition(SDLDevice::instance().getWindow()));
                this->buildMenu();

                return true;
            }
        }
        break;
        default:
            break;
        }

        return false;
    }

    auto GUIInteractionMenu::buildMenu() -> void
    {
        m_entries.clear();

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        // First check if clicked in inventory (or other GUI windows)
        auto rightClickedInInventoryWindow{
            GUIInventoryWindow::instance().getBounds().contains(mousePos)};

        if (GUIInventoryWindow::instance().getVisible() && rightClickedInInventoryWindow)
        {
            m_clickedCoordinate = {-1, -1};

            m_clickedObjects.clear();

            auto object{GUIInventoryWindow::instance().getObjectPtrPtr(mousePos)};

            if (object)
            {
                std::vector<int> objectHashes;

                objectHashes.push_back((*object)->getType());

                m_clickedObjects.push_back(object.get());

                this->showMenuForTileAndObjects(0, objectHashes);

                return;
            }
        }
        // If not clicked in inventory, check if clicked tile

        auto hoveredCoordinate{TileHovering::instance().getHoveredCoordinate()};
        auto worldArea{World::instance().getCurrentWorldArea()};

        m_clickedCoordinate = hoveredCoordinate;

        auto tile{worldArea->getTile(hoveredCoordinate.x, hoveredCoordinate.y)};

        auto objects{tile->getObjectsStack()->getObjects()};

        auto ground{0};

        if (tile)
        {
            ground = tile->getGround();
        }

        std::vector<int> objectHashes;

        for (auto &object : objects)
        {
            auto type{object->getType()};

            objectHashes.push_back(type);
        }

        this->showMenuForTileAndObjects(ground, objectHashes);
    }

    auto GUIInteractionMenu::showMenuForTileAndObjects(int groundHash,
                                                       const std::vector<int> &objectHashes) -> void
    {
        std::vector<Action> actions{getAction<hash("ActionStop")>(),
                                    getAction<hash("ActionLayCobbleStone")>(),
                                    getAction<hash("ActionPlowLand")>(),
                                    getAction<hash("ActionForage")>(),
                                    getAction<hash("ActionCraftStonePickaxe")>(),
                                    getAction<hash("ActionCraftStoneSlab")>(),
                                    getAction<hash("ActionLayStoneSlab")>(),
                                    getAction<hash("ActionCraftStoneBrick")>(),
                                    getAction<hash("ActionCraftStoneWall")>(),
                                    getAction<hash("ActionCraftStoneWallDoor")>(),
                                    getAction<hash("ActionCraftStoneBowl")>(),
                                    getAction<hash("ActionPickBranch")>(),
                                    getAction<hash("ActionPickStone")>(),
                                    getAction<hash("ActionMineStone")>(),
                                    getAction<hash("ActionEatRedApple")>(),
                                    getAction<hash("ActionOpenStoneBowl")>(),
                                    getAction<hash("ActionCraftUnlitCampfire")>(),
                                    getAction<hash("ActionOpenCampfire")>(),
                                    getAction<hash("ActionLightUnlitCampfire")>()};

        auto &inventory{Player::instance().getObjectsInventoryRef()};

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
                if (inventory.countHasObject(invObjectMatch))
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

        this->setHeight(newHeight);
    }

    auto GUIInteractionMenu::handleClick() -> void
    {
        auto bounds{this->getBounds()};

        auto mousePosition{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto i{0};

        for (auto &entry : m_entries)
        {
            auto menuEntryRect{RectF{bounds.x + 0.01f + k_indentWidth,
                                     bounds.y + 0.01f + k_lineHeight * (i + 1), bounds.width,
                                     k_lineHeight}};

            if (menuEntryRect.contains(mousePosition))
            {
                auto worldArea{World::instance().getCurrentWorldArea()};

                auto tile{worldArea->getTile(m_clickedCoordinate)};

                if (tile)
                {
                    auto playerPos{Player::instance().getPosition()};

                    auto absDx{std::abs(m_clickedCoordinate.x - playerPos.x)};
                    auto absDy{std::abs(m_clickedCoordinate.y - playerPos.y)};

                    if (absDx > 1 || absDy > 1)
                    {
                        GUIChatBox::instance().print("You are too far away to do the action.");

                        this->setVisible(false);

                        return;
                    }

                    m_clickedObjects.clear();

                    for (auto obj : tile->getObjectsStack()->getObjects())
                    {
                        m_clickedObjects.push_back(&obj);
                    }
                }

                entry.getAction()(tile, m_clickedObjects);
            }

            this->setVisible(false);

            ++i;
        }

        this->setVisible(false);
    }

    auto GUIInteractionMenu::updateDerived() -> void
    {
        GUIPanel::updateDerived();

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto bounds{this->getBounds()};

        bounds.y += k_lineHeight + 0.01F;

        bounds.height -= k_lineHeight + 2 * 0.01F;

        if (bounds.contains(mousePos))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
        }
    }

    auto GUIInteractionMenu::renderDerived() const -> void
    {
        GUIPanel::renderDerived();

        auto bounds{this->getBounds()};

        TextRenderer::instance().drawString(k_renderIDActionsString, "Actions", bounds.x + 0.01f,
                                            bounds.y + 0.01f, FontSizes::_20, false, true,
                                            Palette::getColor<hash("YellowTransparent")>());

        auto i{0};

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        for (auto &entry : m_entries)
        {
            auto rowBounds{
                RectF{bounds.x, bounds.y + (i + 1) * k_lineHeight, bounds.width, k_lineHeight}};

            if (rowBounds.contains(mousePos))
            {
                Color2DRenderer::instance().drawFilledRectangle(
                    k_renderIDHoveredRow, Palette::getColor<hash("MildBlueTransparent")>(),
                    rowBounds.x, rowBounds.y, rowBounds.width, rowBounds.height, true);
            }

            TextRenderer::instance().drawString(
                m_renderIDsMenuEntryStrings[i], entry.getLabel(), bounds.x + 0.01f + k_indentWidth,
                bounds.y + 0.01f + (i + 1) * k_lineHeight, FontSizes::_20, false, true);

            ++i;
        }
    }
}
