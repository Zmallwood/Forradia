/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIInteractionMenu.hpp"
#include "Actions/actions.hpp"
#include "Core/Update/TileHovering.hpp"
#include "CustomGUI/GUIInventoryWindow.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerObjectsInventory.hpp"
#include "WorldStructure/Object.hpp"
#include "WorldStructure/ObjectsStack.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/GUICore/GUIChatBox.hpp"
#include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
#include "ForradiaEngine/MinorComponents/Cursor.hpp"
#include "ForradiaEngine/Rendering/Colors/Color2DRenderer.hpp"
#include "ForradiaEngine/Rendering/Text/TextRenderer.hpp"

namespace ForradiaEngine::JewelryMakerTheme
{
    auto GUIInteractionMenu::initialize() -> void
    {
        dynamic_cast<GUIPanel *>(this)->setVisible(false);

        for (auto i = 0; i < k_maxNumMenuEntries; i++)
        {
            m_renderIDsMenuEntryStrings.push_back(
                hash("GUIInteractionMenuEntryString" + std::to_string(i)));
        }

        m_actions = {getAction<hash("ActionStop")>(),
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
                     getAction<hash("ActionLightUnlitCampfire")>(),
                     getAction<hash("ActionBuildMineEntrance")>()};
    }

    auto GUIInteractionMenu::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        switch (mouseButton)
        {
        case SDL_BUTTON_LEFT:
        {
            if (dynamic_cast<const GUIComponent *>(this)->getVisible())
            {
                this->handleClickInMenu();
                dynamic_cast<GUIPanel *>(this)->setVisible(false);

                return true;
            }
        }
        break;

        case SDL_BUTTON_RIGHT:
        {
            if (dynamic_cast<const GUIComponent *>(this)->getVisible() == false)
            {
                dynamic_cast<GUIPanel *>(this)->setVisible(true);
                dynamic_cast<GUIPanel *>(this)->setPosition(
                    getNormalizedMousePosition(SDLDevice::instance().getWindow()));
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

        auto hoveredCoordinate{TileHovering::getHoveredCoordinate()};
        auto worldArea{World::instance().getWorldArea(Player::instance().getWorldAreaCoordinate())};

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
        for (auto &action : m_actions)
        {
            bool goOn{false};

            goOn = GUIInteractionMenu::checkActionGroundMatches(action, groundHash);

            if (goOn == false)
            {
                continue;
            }

            goOn = GUIInteractionMenu::checkActionObjectMatches(action, objectHashes);

            if (goOn == false)
            {
                continue;
            }

            goOn = GUIInteractionMenu::checkActionInventoryObjectsMatches(action);

            // If the action passed all checks, then add it to the menu.
            if (goOn)
            {
                m_entries.emplace_back(action.label, action.action);
            }
        }

        auto newHeight{2 * k_margin + k_lineHeight * (m_entries.size() + 1)};

        this->setHeight(newHeight);
    }

    auto GUIInteractionMenu::checkActionGroundMatches(Action &action, int groundHash) -> bool
    {
        bool goOn{false};

        // Check if the ground need to match a specific ground hash.
        for (auto groundMatch : action.groundMatches)
        {
            goOn = groundMatch == groundHash ? true : goOn;
        }

        // If no ground match is needed or the ground hash is 0, then go on with other checks.
        goOn = action.groundMatches.empty() || groundHash == 0 ? true : goOn;

        return goOn;
    }

    auto GUIInteractionMenu::checkActionObjectMatches(Action &action,
                                                      const std::vector<int> &objectHashes) -> bool
    {
        bool goOn{false};

        // Check if the object need to match a specific object hash.
        for (auto objectMatch : action.objectMatches)
        {
            // Check if the object need to match a specific object hash, looking through the
            // object hashes where the mouse was clicked.
            for (auto objectHash : objectHashes)
            {
                goOn = objectMatch == objectHash ? true : goOn;
            }
        }

        // If no object match is needed, then go on with other checks.
        goOn = action.objectMatches.empty() ? true : goOn;

        return goOn;
    }

    auto GUIInteractionMenu::checkActionInventoryObjectsMatches(Action &action) -> bool
    {
        auto &inventory{Player::instance().getObjectsInventoryRef()};

        bool goOn{false};

        // Check if the action need to match a specific object in the inventory.
        for (auto invObjectMatch : action.objectsInInventory)
        {
            // Check if the object to match is in the inventory.
            goOn = inventory.countHasObject(invObjectMatch) > 0 ? true : goOn;
        }

        // If no object in inventory object match is needed, then then go on.
        goOn = action.objectsInInventory.empty() ? true : goOn;

        return goOn;
    }

    auto GUIInteractionMenu::handleClickInMenu() -> void
    {
        auto bounds{this->getBounds()};

        auto mousePosition{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto idx{0};

        for (auto &entry : m_entries)
        {
            auto rowBounds{
                RectF{bounds.x, bounds.y + (idx + 1) * k_lineHeight, bounds.width, k_lineHeight}};

            if (rowBounds.contains(mousePosition))
            {
                auto worldArea{
                    World::instance().getWorldArea(Player::instance().getWorldAreaCoordinate())};

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

            ++idx;
        }

        this->setVisible(false);
    }

    auto GUIInteractionMenu::updateDerived() -> void
    {
        GUIPanel::updateDerived();

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto bounds{this->getBounds()};

        bounds.y += k_lineHeight + k_margin;

        bounds.height -= k_lineHeight + 2 * k_margin;

        if (bounds.contains(mousePos))
        {
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
        }
    }

    auto GUIInteractionMenu::renderDerived() const -> void
    {
        GUIPanel::renderDerived();

        auto bounds{this->getBounds()};

        TextRenderer::instance().drawString(k_renderIDActionsString, "Actions", bounds.x + k_margin,
                                            bounds.y + k_margin, FontSizes::_20, false, true,
                                            Palette::getColor<hash("YellowTransparent")>());

        auto idx{0};

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        for (const auto &entry : m_entries)
        {
            auto rowBounds{
                RectF{bounds.x, bounds.y + (idx + 1) * k_lineHeight, bounds.width, k_lineHeight}};

            if (rowBounds.contains(mousePos))
            {
                Color2DRenderer::instance().drawFilledRectangle(
                    k_renderIDHoveredRow, Palette::getColor<hash("MildBlueTransparent")>(),
                    rowBounds.x, rowBounds.y, rowBounds.width, rowBounds.height, true);
            }

            TextRenderer::instance().drawString(m_renderIDsMenuEntryStrings[idx], entry.getLabel(),
                                                bounds.x + k_margin + k_indentWidth,
                                                bounds.y + k_margin + (idx + 1) * k_lineHeight,
                                                FontSizes::_20, false, true);

            ++idx;
        }
    }
}
