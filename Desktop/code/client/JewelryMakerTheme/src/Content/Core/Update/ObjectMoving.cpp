/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "ObjectMoving.hpp"
    #include "Content/CustomGUI/GUIInventoryWindow.hpp"
    #include "Content/WorldStructure/Object.hpp"
    #include "ForradiaEngine/Common/Utilities.hpp"
    #include "ForradiaEngine/GraphicsDevices/SDLDevice.hpp" 
    #include "ForradiaEngine/Rendering/Images/Image2DRenderer.hpp"
// clang-format on

namespace ForradiaEngine::JewelryMakerTheme
{
    auto ObjectMoving::onMouseDown(Uint8 mouseButton) -> bool
    {
        /* Pick up object from inventory */ // clang-format off
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
        // clang-format on

        return false;
    }

    auto ObjectMoving::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        if (m_objectInAir)
        {
            /* Drop object into inventory */ // clang-format off
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
            // clang-format on
        }

        return false;
    }

    auto ObjectMoving::render() const -> void
    {
        if (m_objectInAir)
        {
            /* Render object in air at mouse position */ // clang-format off
                auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

                Image2DRenderer::instance().drawImageByHash(
                    k_renderIDImage, m_objectInAir->getType(), mousePos.x, mousePos.y,
                    k_objectImageWidth,
                    convertWidthToHeight(k_objectImageWidth, SDLDevice::instance().getWindow()), true);
            // clang-format on
        }
    }
}
