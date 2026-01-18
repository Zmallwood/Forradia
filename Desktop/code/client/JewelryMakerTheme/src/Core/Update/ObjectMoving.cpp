/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ObjectMoving.hpp"
#include "CustomGUI/GUIInventoryWindow.hpp"
#include "WorldStructure/Object.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Devices/SDLDevice.hpp"
#include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
#include "TileHovering.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/ObjectsStack.hpp"
#include "Player/Player.hpp"
#include "Properties/ObjectIndex.hpp"
#include "ForradiaEngine/ScenesCore.hpp"
#include "ForradiaEngine/GUICore/GUI.hpp"
#include <SDL2/SDL_mouse.h>

namespace ForradiaEngine::JewelryMakerTheme
{
    auto ObjectMoving::onMouseDown(Uint8 mouseButton) -> bool
    {
        If(this->checkMouseDownInInventoryWindow(mouseButton))
        {
            return true;
        }

        If(this->checkMouseDownInAnyContainerWindow(mouseButton))
        {
            return true;
        }

        If(mouseButton == SDL_BUTTON_LEFT)
        {
            auto hoveredCoordinate{TileHovering::instance().getHoveredCoordinate()};

            auto playerPosition{Player::instance().getPosition()};

            auto absDx{std::abs(hoveredCoordinate.x - playerPosition.x)};
            auto absDy{std::abs(hoveredCoordinate.y - playerPosition.y)};

            If(absDx > 1 || absDy > 1)
            {
                return false;
            }

            auto worldAreaCoordinate{Player::instance().getWorldAreaCoordinate()};

            auto hoveredTile{
                World::instance().getWorldArea(worldAreaCoordinate)->getTile(hoveredCoordinate)};

            auto objectsStack{hoveredTile->getObjectsStack()};

            auto topObject{objectsStack->getTopObject()};

            If(!m_objectInAir && topObject)
            {
                auto canBePickedUp{ObjectIndex::instance().getCanBePickedUp(topObject->getType())};

                If(!canBePickedUp)
                {
                    return false;
                }

                m_objectInAir = objectsStack->popObject();

                m_ticksSinceMouseDownOnTile = getTicks();

                return true;
            }
        }

        return false;
    }

    auto ObjectMoving::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        If(m_objectInAir)
        {
            auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

            auto inventoryWindowBounds{GUIInventoryWindow::instance().getBounds()};

            If(GUIInventoryWindow::instance().getVisible() &&
               inventoryWindowBounds.contains(mousePos) && mouseButton == SDL_BUTTON_LEFT)
            {
                If(auto objectPtrPtr{GUIInventoryWindow::instance().getObjectPtrPtr(mousePos)})
                {
                    *objectPtrPtr = m_objectInAir;

                    Player::instance().addPlayerAction(
                        PlayerActionTypes::Move,
                        GUIInventoryWindow::instance().getContainerObjectType(), {-1, -1},
                        *objectPtrPtr);

                    m_objectInAir = nullptr;

                    return true;
                }
            }

            If(mouseButton == SDL_BUTTON_LEFT)
            {
                auto mainScene{SceneManager::instance().getScene("MainScene")};

                auto gui{mainScene->getGUI()};

                auto childComponents{gui->getChildComponentsRecursively()};

                Loop(const auto &childComponent : childComponents)
                {
                    auto castedToGUIContainerWindow{
                        std::dynamic_pointer_cast<GUIContainerWindow>(childComponent)};

                    If(castedToGUIContainerWindow)
                    {
                        auto bounds{castedToGUIContainerWindow->getBounds()};

                        If(bounds.contains(mousePos))
                        {
                            If(auto objectPtrPtr{
                                castedToGUIContainerWindow->getObjectPtrPtr(mousePos)})
                            {
                                *objectPtrPtr = m_objectInAir;

                                Player::instance().addPlayerAction(
                                    PlayerActionTypes::Move,
                                    castedToGUIContainerWindow->getContainerObjectType(), {-1, -1},
                                    *objectPtrPtr);

                                m_objectInAir = nullptr;

                                return true;
                            }
                        }
                    }
                }
            }

            auto hoveredCoordinate{TileHovering::instance().getHoveredCoordinate()};

            auto worldAreaCoordinate{Player::instance().getWorldAreaCoordinate()};

            auto hoveredTile{
                World::instance().getWorldArea(worldAreaCoordinate)->getTile(hoveredCoordinate)};

            auto objectsStack{hoveredTile->getObjectsStack()};

            objectsStack->addObject(m_objectInAir);

            Player::instance().addPlayerAction(PlayerActionTypes::Move,
                                               (*objectsStack->getTopObjectPtrPtr())->getType(),
                                               {-1, -1}, *objectsStack->getTopObjectPtrPtr());

            m_objectInAir = nullptr;

            If(clickSpeed < k_clickSpeedThreshold)
            {
                return false;
            }

            return true;
        }

        return false;
    }

    auto ObjectMoving::checkMouseDownInInventoryWindow(Uint8 mouseButton) -> bool
    {
        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto inventoryWindowBounds{GUIInventoryWindow::instance().getBounds()};

        If(!m_objectInAir && GUIInventoryWindow::instance().getVisible() &&
           inventoryWindowBounds.contains(mousePos) && mouseButton == SDL_BUTTON_LEFT)
        {
            If(auto objectPtrPtr{GUIInventoryWindow::instance().getObjectPtrPtr(mousePos)})
            {
                m_objectInAir = *objectPtrPtr;

                *objectPtrPtr = nullptr;

                return true;
            }
        }

        return false;
    }

    auto ObjectMoving::checkMouseDownInAnyContainerWindow(Uint8 mouseButton) -> bool
    {

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        If(!m_objectInAir && mouseButton == SDL_BUTTON_LEFT)
        {
            auto mainScene{SceneManager::instance().getScene("MainScene")};

            auto gui{mainScene->getGUI()};

            auto childComponents{gui->getChildComponentsRecursively()};

            Loop(const auto &childComponent : childComponents)
            {
                auto castedToGUIContainerWindow{
                    std::dynamic_pointer_cast<GUIContainerWindow>(childComponent)};

                If(castedToGUIContainerWindow)
                {
                    auto bounds{castedToGUIContainerWindow->getBounds()};

                    If(bounds.contains(mousePos))
                    {
                        If(auto objectPtrPtr{castedToGUIContainerWindow->getObjectPtrPtr(mousePos)})
                        {
                            m_objectInAir = *objectPtrPtr;

                            *objectPtrPtr = nullptr;

                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    auto ObjectMoving::render() const -> void
    {
        If(m_objectInAir && getTicks() - m_ticksSinceMouseDownOnTile > k_clickSpeedThreshold)
        {
            auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

            Image2DRenderer::instance().drawImageByHash(
                k_renderIDImage, m_objectInAir->getType(), mousePos.x, mousePos.y,
                k_objectImageWidth,
                convertWidthToHeight(k_objectImageWidth, SDLDevice::instance().getWindow()), true);
        }
    }
}
