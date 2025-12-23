/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "ObjectMoving.hpp"
#include "CanvasUtilities.hpp"
#include "GUIInventoryWindow.hpp"
#include "Image2DRenderer.hpp"
#include "MouseUtilities.hpp"
#include "Object.hpp"
#include "SDLDevice.hpp"

namespace Forradia::Theme0
{
    auto ObjectMoving::OnMouseDown(Uint8 mouseButton) -> bool
    {
        auto mousePos{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};

        auto inventoryWindowBounds{GUIInventoryWindow::Instance().GetBounds()};

        if (!m_objectInAir && GUIInventoryWindow::Instance().GetVisible() &&
            inventoryWindowBounds.Contains(mousePos) && mouseButton == SDL_BUTTON_LEFT)
        {
            auto objectPtrPtr{GUIInventoryWindow::Instance().GetObjectPtrPtr(mousePos)};

            if (objectPtrPtr)
            {
                m_objectInAir = *objectPtrPtr;

                *objectPtrPtr = nullptr;

                return true;
            }
        }

        return false;
    }

    auto ObjectMoving::OnMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        if (m_objectInAir)
        {
            auto mousePos{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};

            auto inventoryWindowBounds{GUIInventoryWindow::Instance().GetBounds()};

            if (GUIInventoryWindow::Instance().GetVisible() &&
                inventoryWindowBounds.Contains(mousePos) && mouseButton == SDL_BUTTON_LEFT)
            {
                auto objectPtrPtr{GUIInventoryWindow::Instance().GetObjectPtrPtr(mousePos)};

                if (objectPtrPtr)
                {
                    *objectPtrPtr = m_objectInAir;

                    m_objectInAir = nullptr;

                    return true;
                }
            }
        }
        return false;
    }

    auto ObjectMoving::Render() const -> void
    {
        if (m_objectInAir)
        {
            auto mousePos{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};

            Image2DRenderer::Instance().DrawImageByHash(
                k_renderIDImage, m_objectInAir->GetType(), mousePos.x, mousePos.y,
                k_objectImageWidth,
                ConvertWidthToHeight(k_objectImageWidth, SDLDevice::Instance().GetWindow()), true);
        }
    }
}
