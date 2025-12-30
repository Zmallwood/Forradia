/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ObjectMoving.hpp"
#include "CustomGUI/GUIInventoryWindow.hpp"
#include "WorldStructure/Object.hpp"
#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp"
#include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
#include "TileHovering.hpp"
#include "WorldStructure/World.hpp"
#include "WorldStructure/WorldArea.hpp"
#include "WorldStructure/Tile.hpp"
#include "WorldStructure/ObjectsStack.hpp"
#include "Player/Player.hpp"
#include <SDL2/SDL_mouse.h>

namespace ForradiaEngine::JewelryMakerTheme
{
    auto ObjectMoving::onMouseDown(Uint8 mouseButton) -> bool
    {
        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        auto inventoryWindowBounds{GUIInventoryWindow::instance().getBounds()};

        if (!m_objectInAir && GUIInventoryWindow::instance().getVisible() &&
            inventoryWindowBounds.contains(mousePos) && mouseButton == SDL_BUTTON_LEFT)
        {
            if (auto objectPtrPtr{GUIInventoryWindow::instance().getObjectPtrPtr(mousePos)})
            {
                m_objectInAir = *objectPtrPtr;

                *objectPtrPtr = nullptr;

                return true;
            }
        }

        if (mouseButton == SDL_BUTTON_LEFT)
        {

            auto hoveredCoordinate{TileHovering::instance().getHoveredCoordinate()};

            auto playerPosition{Player::instance().getPosition()};

            auto absDx{std::abs(hoveredCoordinate.x - playerPosition.x)};
            auto absDy{std::abs(hoveredCoordinate.y - playerPosition.y)};

            if (absDx > 1 || absDy > 1)
            {
                return false;
            }

            auto worldAreaCoordinate{Player::instance().getWorldAreaCoordinate()};

            auto hoveredTile{
                World::instance().getWorldArea(worldAreaCoordinate)->getTile(hoveredCoordinate)};

            auto objectsStack{hoveredTile->getObjectsStack()};

            if (!m_objectInAir && objectsStack->getSize() > 0)
            {
                m_objectInAir = objectsStack->popObject();

                return true;
            }
        }

        return false;
    }

    auto ObjectMoving::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        if (m_objectInAir)
        {
            auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

            auto inventoryWindowBounds{GUIInventoryWindow::instance().getBounds()};

            if (GUIInventoryWindow::instance().getVisible() &&
                inventoryWindowBounds.contains(mousePos) && mouseButton == SDL_BUTTON_LEFT)
            {
                if (auto objectPtrPtr{GUIInventoryWindow::instance().getObjectPtrPtr(mousePos)})
                {
                    *objectPtrPtr = m_objectInAir;

                    m_objectInAir = nullptr;

                    return true;
                }
            }

            auto hoveredCoordinate{TileHovering::instance().getHoveredCoordinate()};

            auto worldAreaCoordinate{Player::instance().getWorldAreaCoordinate()};

            auto hoveredTile{
                World::instance().getWorldArea(worldAreaCoordinate)->getTile(hoveredCoordinate)};

            auto objectsStack{hoveredTile->getObjectsStack()};

            objectsStack->addObject(m_objectInAir);

            m_objectInAir = nullptr;

            if (clickSpeed < 200)
            {
                return false;
            }

            return true;
        }

        return false;
    }

    auto ObjectMoving::render() const -> void
    {
        if (m_objectInAir)
        {
            auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

            Image2DRenderer::instance().drawImageByHash(
                k_renderIDImage, m_objectInAir->getType(), mousePos.x, mousePos.y,
                k_objectImageWidth,
                convertWidthToHeight(k_objectImageWidth, SDLDevice::instance().getWindow()), true);
        }
    }
}
